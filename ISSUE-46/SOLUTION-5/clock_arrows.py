#!/usr/bin/env python
#-*- coding:utf-8 -*-
''' 
 2014-03-14 by kantal59
 License: LGPL
 OLIMEX WPC#46: Clock Arrows
            Clock minute and hour arrows cross as they revolve around.
            Make code that compute how many times the arrows cross in one twelve hour period, and print list of those times.
           
            Hour arrow speed, Rh= 1/43200 RPS;  minute arrow speed, Rm: 1/3600 RPS
            There is crossing when for the displacements Rh*t == Rm*t-R, where t is in seconds and R is the full revolutions 
            of the faster minute arrow, R=0,1,..12 .
            t=R/(Rm-Rh)
'''
Rh= float(1)/43200
Rm= float(1)/3600
d= Rm-Rh 
for R in range(0,12):
    t= int(R/d)     # seconds
    h,s= divmod(t,3600)
    m,s= divmod(s,60)
    
    print( "{0:02d}:{1:02d}:{2:02d}".format( h,m,s) )
