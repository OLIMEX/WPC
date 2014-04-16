/*
 2014-05-11 by kantal59
 License: LGPL
 Compile: gcc -o hbot  hbot.c -lm
 
 OLIMEX WPC#52: H-bot
 			H-bot is simple way to control X-Y CNC table with just two stepper motors and string. 
 			More on the subject you can find on the net.
 			Make code which moves the CNC table at position X,Y by rotating the two stepper motors. 
 			You know the string length, motor shaft diameter, etc parameters. Starting from center 0,0 
 			you calculate the rotation angle of both motors when new X,Y coordinate is entered. 
 			0,0 is in the center so XY can be positive and negative.
 			
 			Resources: http://multimechatronics.com/build_a_h-bot.php
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct {	float x; float y; } point_t;
typedef struct { 	float ra; float rb; } rot_t;


void relmove( point_t *pt, rot_t *rt, float radius )
/*  "Relative move'. It returns the rotation values for move to the new position 'pt' from the current position.
	Input:	
		pt: 	 x,y coordinates of the target point relative the current position
		radius:	 the radius of driving pulleys
		rt:		 storage address for the output
	Output:
		rt: 	 the rotation values for the pulleys
*/
{
	// H-bot kinematics:
	if( radius <=0 ) return;
	rt->ra= ( pt->y - pt->x)/ radius;
	rt->rb= -( pt->y + pt->x)/ radius;
} 


float posctrl( float T, float t)
/*
	It returns a value beetwen 0.0 and 1.0 to scale the displacement.
	T: the total time of movment
	t: continuous time  [ 0, T]
*/
{
	float rslt,tmp;
	if( T<=0 || t<=0 ) return(0);
	if( t>= T)  return( 1.0);
	rslt= tmp= pow( t/T,3);
	rslt*=10;	tmp*=(t/T);
	rslt+= -15*tmp +6*tmp*(t/T);
	return( rslt);
}



int segment( point_t *trgpt, float T, float dt, float radius, rot_t *rtbuff, unsigned int nrt )
/*
	It calculates the rotations with acceleration control.
	Input:
		trgpt:	target point
		T:		total time of movement
		dt:		interval beetwen elemental movements
		radius: driving pulley radius
		rtbuff:	storage for rotaion values
		nrt:	number of rotation pairs fit in rtbuff
	Output:
		rtbuff:	rotation values
	Return:		
			number of rotation pairs in rtbuff	
*/
{
	float t,sc,L,l,x,y;
	point_t curpt, relpt;	
	rot_t rot;	
	int i;
	
	if( !nrt) return(0);
	
	curpt.x= curpt.y= rtbuff[0].ra= rtbuff[0].rb= 0;
	t= dt;
	L= sqrt( trgpt->x * trgpt->x + trgpt->y * trgpt->y ); 
	
	for( i=1;	i< nrt;		i++){

		sc= posctrl( T,t);
		l= L*sc;
		x= trgpt->x * l/L;		y= trgpt->y * l/L;
		relpt.x= x - curpt.x;	relpt.y= y - curpt.y;	
		relmove( &relpt, &rot, radius);
		
		rtbuff[i].ra= rot.ra;		rtbuff[i].rb= rot.rb;
		
		if( sc == 1.0) return( i);
		
		curpt.x= x;					curpt.y= y;
		t+= dt;
	}

	return(i);
}




int main( int argc, char *argv[])
{

#define NROT	30 
 point_t pt;
 rot_t  rt;
 float radius,T, interval;
 char *endptr;
 unsigned int i, n;
 
 rot_t rot[NROT];
 
 
 if( argc!=4){	puts(" \nUsage: $ hbot x y radius\n where the values are floats\n"); 	return(1);	}
 
 pt.x= strtof( argv[1], &endptr);		if( endptr == argv[1] ) return(2);
 pt.y= strtof( argv[2], &endptr);		if( endptr == argv[2] ) return(3);
 radius= strtof( argv[3], &endptr); 	if( endptr == argv[3]  ||  radius <=0 ) return(4);
 
 printf("\n Start (0,0) -> target (%f, %f) with driving pulley radius %f\n", pt.x,pt.y, radius);
 
 relmove( &pt,&rt,radius);
 printf( " Rotation for simple move: %f, %f \n", rt.ra,rt.rb);
 
 T=10;	interval= 1;
 n= segment( &pt, T, interval, radius, rot, NROT);
 printf( " Rotations with acceleration control\n  number of rotations: %d\n  total time of movement(T): %f\n  interval(dT): %f\n",n,T,interval);
 rt.ra=0;	rt.rb=0;
 for( i=0;	i<n;	 i++){
 	printf("  %f, %f\n", rot[i].ra,rot[i].rb );
 	rt.ra+= rot[i].ra;	rt.rb+= rot[i].rb;  	  	
 }	
 printf("  total: %f, %f\n\n", rt.ra, rt.rb);


 return(0);
}
