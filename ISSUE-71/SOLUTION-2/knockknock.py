#!/usr/bin/env python3
#-*- coding:utf-8 -*-
''' 
 2014-12-07 by kantal59
 License: GPL
 OLIMEX WPC#71: Knock Lock
	 Make code which implements knock pattern recognition for door open/close. There must be option to learn knock sequence.
	 Then every time when this sequence is implemented door lock opens and you signal this.
	 To simplify the lock we assume between knocks there will be only two intervals short and long.
	 For instance your code should be able to “learn” this sequence:  knock-short-knock-short-knock-long-knock-long-knock-long-knock 
	 i.e. three fast and three slow knocks and this to open the door.
	 For knock detecting you can use SPACE key press for instance.

	 The solution does not use fixed time values for short and long intervals, the values will be determined from the actual sequence.
	 There are must be at least three knocking until the time expires (timeout), and the sequence must have both short and long knocking.
	 If the determined time values differ only a little (see 'threshold') from the mean value, then they are considered as ambiguous.
	 The input sequence will be compared with ones in the config file and if it matches then the corresponding 'action' will be displayed.
	 A new sequence can be saved as an action. The config file is an editable text file (INI-file).
'''
import select,sys,termios,fcntl,os,time
import configparser


timeout= 4		# sec
threshold= 10	# percent 
tshort, tlong = '.', '_'
fncfg= "knock.cfg"

# --- UTILS -----------------------------
def init_stdin():
# To read one char only at a time; it works on Linux
# http://effbot.org/pyfaq/how-do-i-get-a-single-keypress-at-a-time.htm

	fno = sys.stdin.fileno()
	oldattr = termios.tcgetattr(fno)
	newattr = oldattr[:]
	newattr[3] = newattr[3] & ~termios.ICANON & ~termios.ECHO
	termios.tcsetattr(fno, termios.TCSANOW, newattr)

	oldflags = fcntl.fcntl(fno, fcntl.F_GETFL)
	fcntl.fcntl(fno, fcntl.F_SETFL, oldflags | os.O_NONBLOCK)
	return(sys.stdin)


def reset_stdin():

	fno = sys.stdin.fileno()
	attr = termios.tcgetattr(fno)
	attr[3] = attr[3] | termios.ICANON | termios.ECHO
	termios.tcsetattr(fno, termios.TCSANOW, attr)

	flags = fcntl.fcntl(fno, fcntl.F_GETFL)
	fcntl.fcntl(fno, fcntl.F_SETFL, flags & ~os.O_NONBLOCK)


# --- THE PROBLEM ---------------------------------

def get_sequence( verbose=False):
	global timeout,tshort,tlong,threshold

	knocks=[]
	stdin= init_stdin()
	po= select.poll()
	po.register( stdin.fileno(), select.POLLIN)	# stdin

	tout= timeout*1000
	if verbose:		print(" timeout= {} sec".format(timeout))
	while True:
		events= po.poll( tout)	# msecs
	
		if not events:
			reset_stdin()
			break
			
		for fd, ev in events:
			if fd == stdin.fileno():
				s= stdin.read(1)
				knocks.append( time.time())
				continue
			
			
	ambiguous= False
	tims=[]
	if len(knocks) <= 1:
		ambiguous= True
	else:
		
		knocks= [ knocks[i]-knocks[i-1] for i in range(1,len(knocks)) ]
		tmax,tmin = max( knocks), min(knocks)
		tmiddle = (tmax+tmin)/2
		tims= [ tshort if t<=tmiddle else tlong 	for t in knocks ]
		if verbose:		print(" max/min/middle = {:.2f}/{:.2f}/{:.2f}".format( tmax,tmin,tmiddle))
		for t in knocks:
			diff= (t-tmiddle)*100/tmiddle
			if abs(diff) < threshold: 		ambiguous= True
			if verbose:		print(" {:.2f} [{:.0f}%] {}".format(t, diff, '*' if abs(diff) < threshold else '' ) )
	
		if verbose:
			if ambiguous:
				print( " Ambiguous time differences\n")
			else:
				print(" knocks = {}\n the sequence: ".format( len(tims)+1),end='')
				for t in tims:		print("{}".format(t),end='')
				print()
	
	return( not ambiguous, ''.join(tims) )	


#---------------------------------------------------

if __name__ == "__main__":

	cfg= configparser.ConfigParser()
	cfg.read( fncfg)
	if "Actions" not in cfg.sections():		cfg["Actions"]={}
	
	while True:
	
		print(60*'-')
		answ= input(" 'Enter' to read knock sequence or 'q'+'Enter' to quit= ").strip()
		if answ == "q":
			fob= open(fncfg,"w")
			cfg.write( fob)
			exit(0)
			
		ok,seq= get_sequence(True)
		if not ok:		continue
		found= False
		for  act,pattern  in cfg.items("Actions"):
			if pattern == seq:
				print( " sequence matches action ---> {} ".format( act))
				found= True
				break
		
		if not found:
			answ= input(" Give an action name to save or only press 'Enter' to continue=").strip()	
			if not answ:	continue
			cfg["Actions"][answ]= seq
		
	
	
	
	
	
