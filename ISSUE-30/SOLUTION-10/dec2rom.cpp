/**
 *******************************************************************************
 * Copyright 2013 Troy Korjuslommi.
 * All Rights Reserved.
 *******************************************************************************
 *  
 * I      1
 * V      5
 * X     10
 * L     50
 * C    100
 * D    500
 * M   1000
 * 
 * Specs: 1,000 (M) is the largest value we can represent.
 * The wikipedia article for the question didn't specify syntax for values above 3,999.
 * Would 4,000 be MMMM or IVM? How about 0? Because I didn't want to refer to external
 * docs for syntax, I concluded that a valid range must be 1..3999 i.e. I..MMMCMXCIX.
 *
 * Output is formatted so that it is easy to read the output for debugging.
 * With the line of bash below you can print a sample set of values for manual
 * testing.
 * val=1 && while [ $val -lt 4000 ];do ./dec2rom $val;let val=$val+71;done
 *
 * The code is C++ using C++11 syntax, so a compiler which supports C++11
 * is required.
 * If using g++, build with:
 * g++ -Wall -std=c++0x dec2rom.cpp -o dec2rom
 *
 */


#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stdexcept>
#include <cstdio>

using std::string;
using std::stringstream;
using std::map;
using std::runtime_error;


const uint32_t MINDEC = 1;
const uint32_t MAXDEC = 3999;

map<uint32_t,char> maxtable{ 
    { 1000, 'M' }
   ,{ 500,  'D' }
   ,{ 100,  'C' }
   ,{  50,  'L' }
   ,{  10,  'X' }
   ,{   5,  'V' }
   ,{   1,  'I' }
};

map<uint32_t,std::pair<uint32_t,string>> neartable{ 
     {  500, std::make_pair(900, "CM") }
   , {  100, std::make_pair(400, "CD") }
   , {   50, std::make_pair( 90, "XC") }
   , {   10, std::make_pair( 40, "XL") }
   , {    5, std::make_pair(  9, "IX") }
   , {    1, std::make_pair(  4, "IV") }
};


uint32_t print(std::ostream& os, uint32_t value, uint32_t max);
string dec2rom(uint32_t value);

string dec2rom(uint32_t value) {
	stringstream s;
	if (value < MINDEC || value > MAXDEC) throw runtime_error("Input value out of range.");
	int vals[]{1000,500,100,50,10,5,1,0};
	for (int * p = vals; *p; ++p) {
		value = print(s, value, *p);
	}
	return s.str();
}

uint32_t print(std::ostream& os, uint32_t value, uint32_t max) {
	auto near = neartable.find(max);
	if (near != neartable.end()) {
		const uint32_t& n   = near->second.first;
		const string&   str = near->second.second;
		if (value >= n) {
			os << str;
			value -= n;
		}
	}
	while (value >= max) {
		os << maxtable[max];
		value -= max;
	}
	return value;
}



int main(int argc, char ** argv) {
	try {
		if (argc < 2) 
			throw runtime_error("USAGE: dec2rom decimal_number");
		stringstream s;
		s.str(argv[1]);
		uint32_t value = 0;
		s >> value;
		if (! s.eof()) 
			throw runtime_error("Junk input.\nUSAGE: dec2rom decimal_number");
		char buf[6]{0};
		snprintf(buf, sizeof(buf), "%-4d", value);
		std::cout << buf << "   " << dec2rom(value) << "\n";

	} catch (const std::exception& ex) {
		std::cerr << "*** Error: " << ex.what() << "\n";
	}
}





