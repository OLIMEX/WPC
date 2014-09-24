#!/bin/bash

#Version: 0.1
#Author: kaloyan_petrov@mail.bg

#Description: Solution to weekly challenge 65
#http://olimex.wordpress.com/2014/09/19/weekend-programming-challange-week-65-pcb-resistance-calculator/

#http://actpcb.com/via-calculator
#http://circuitcalculator.com/wordpress/2006/01/24/trace-resistance-calculator

#constants
readonly RESISTIVITY='1.9*(10^-5)' 			#Ohm-mm (plated copper)
readonly COPPER_RESISTIVITY='1.7*(10^-5)'	#ohm-mm (pure copper)
readonly TEMP_CO='3.9*(10^-3)'				#ohm/ohm/C
readonly TEMP=25							#temperature C
readonly VIA_LENGTH=2						#mm

function calc(){ 	echo "scale=10; ${1}" | bc; }

echo "Line resistance calculator ver. 0.1"

echo "Track parameters"
read -p "Width (mm): " LINE_WIDTH
read -p "Thickness (mm): " LINE_THICK
read -p "Length (mm): " LINE_LENGTH

echo "Vias parameters:"
read -p "Count: " VIAS_COUNT
if [ ${VIAS_COUNT} -gt 0 ]; then

	read -p "Thickness (mm): " VIA_THICK
	read -p "Diameter (mm): " VIA_DIAM

	#Calculate via resistance
	VIA_AREA=$(calc "3.14*(${VIA_DIAM}+${VIA_THICK})*${VIA_THICK}")
	VIA_RESISTANCE=$(calc "${RESISTIVITY}*${VIA_LENGTH}/${VIA_AREA}");
	VIAS_RESISTANCE=$(calc "${VIAS_COUNT}*${VIA_RESISTANCE}")
else
	VIAS_RESISTANCE=0;
fi

#Calculate line resistance
LINE_AREA=$(calc "${LINE_THICK}*${LINE_WIDTH}")
LINE_RESISTANCE=$(calc "${COPPER_RESISTIVITY}*(${LINE_LENGTH}/${LINE_AREA})*(1+(${TEMP_CO}*(${TEMP}-25)))")

TOTAL_RESISTANCE=$(calc "${VIAS_RESISTANCE}+${LINE_RESISTANCE}")

echo "Resistance is ${TOTAL_RESISTANCE} Ohms"
