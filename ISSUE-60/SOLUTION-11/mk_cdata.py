#!/usr/bin/env python3
#-*- coding:utf-8 -*-
#
# 2014-07-06 by kantal59 
# License: LGPL
# Utility for OLIMEX WPC#60.
# It creates C header file for the datas. The kty.py module is required ( see my Python solution!)

import kty

h= open("kty.h","w")

h.write("// Created by mk_cdata.py\n#ifndef _KTY_H\n#define _KTY_H\n\n#define INVTEMPR	(-273)\n\
#include <inttypes.h>\n\n\
typedef struct { uint32_t res; int16_t temp; } restemp_t;\t // res: resistance in 100th Ohm; temp: temperature in 100th Celsius \n\
typedef struct { size_t len; restemp_t* ptbl; } rtdata_t;\n\n")

#-------- KTY81 110 -----------------
table= kty.TBL_kty81_110
tlen= len(kty.TBL_kty81_110)
device_name= "kty81_110"

c_table_name= "tbl_"+ device_name
c_data_name= "data_"+ device_name

h.write( "restemp_t "+ c_table_name+"["+ str(tlen)+  "]= { // It must be in ascending order by the resistance value.\n" )

for i, (r,t) in enumerate(table):
	if i!=0:		h.write(',')
	if not i%8:	h.write('\n')
	h.write("{ "+ "{0},{1}".format( int(r*100), int(t*100)) + "}"  )

h.write("\n};\n\nrtdata_t "+ c_data_name+ "={" + str(tlen) + ","+ c_table_name + "};" )
#-----------------------------------


h.write("\n#endif\n\n")
h.close()



