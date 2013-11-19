 2013-11-15 by kantal59
 OLIMEX WPC#33: Infinite Output
     Write the shortest possible code which will make infinite output.
     
     
My solutions:

    top -b              # 6 chars;  bash script; usage: $ bash ./script_name
    ping localhost      # 14 chars; bash script; usage: $ bash ./script_name
    
    while 1:print 1     # 15 chars; python 2.x;  usage: $ python2 script_name
    while 1:print(1)    # 16 chars; python 3.x;  usage: $ python3 script_name
    
    main(){while(puts("1"));}   # 25 chars; C, compile: gcc -o prog_name prog.c
    
