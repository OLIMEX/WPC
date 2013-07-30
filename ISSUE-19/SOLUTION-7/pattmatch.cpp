/* 2013-07-28 by kantal59
   License: LGPL
   Compile: g++ -std=c++0x -o pattmatch pattmatch.cpp
   OLIMEX WPC#19: Pattern match
         Make function match() which takes as input input_string and pattern_string, the input strings may contain any ASCII codes
        there are two special codes for use in the pattern-string: ?-replaces 1 character and * – replaces any character(s)
        The function should print all words from the input-string which match the pattern-string
        words can be separated by any of these characters: ‘ ” . , : ;  
        If the input-string have this content “The big black cat jump over the window”

        if pattern-string is “b*” should print
            big
            black

        if pattern-string is “*c*” should print
            black
            cat

        if pattern-string is “?i*” should print
            big
            window
   
   
   The 2nd solution. While the python version do own algorithm, this version uses regular expressions converting '?' into '[0-9a-zA-Z]'
   and '*' into '[0-9a-zA-Z]*' .
   It is a mixed C and C++ code; C++ for easy string manipulation and C for regex as the C++11 regex functions are not fully 
   supported in g++ yet.
   
*/

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <regex.h>  // pure C

using namespace std;


//----------------------------------------------------------
    vector<string> match( string inp, string pattern)
//----------------------------------------------------------
{
 #define nsubm 2
 regmatch_t matchptr [nsubm];
 regex_t cregex;
 string patt1("[0-9a-zA-Z]"); 
 string patt2("[0-9a-zA-Z]*");
 vector<string> wmatched;
 if( !pattern.size()) return( wmatched);

 string patt( pattern);
 size_t pos= patt.find('?');
 while( pos!= string::npos){
    patt.replace( pos, 1, patt1);
    pos= patt.find('?', pos+patt1.size() );
 }
 
 pos= patt.find('*');
 while( pos!= string::npos){
    patt.replace( pos, 1, patt2);
    pos= patt.find('*', pos+patt2.size() );
 }
  
 patt="\\b("+patt+")\\b";

 if( regcomp( &cregex, patt.c_str(), REG_EXTENDED) !=0 ){
    cout << "Regex compile error.\n";
    return( wmatched);
 }

 
 const char *ptr= inp.c_str();  
  
 while( *ptr  &&  regexec( &cregex, ptr, nsubm, matchptr, 0) == 0 ){

    if( matchptr[1].rm_so== -1 ) break;
	int length= matchptr[1].rm_eo - matchptr[1].rm_so; 
	wmatched.push_back( string( ptr+ matchptr[1].rm_so, length) );
	
	ptr+= matchptr[1].rm_eo;
 }	

  regfree( &cregex);
  return( wmatched);
}

//------------------------------
//       T E S T I N G
//------------------------------  
int main( int argc, char *argv[])
{

 string input("The,big., black: cat jump over the bigest window!");
 vector<string> patt={ {"b*"}, {"*c*"}, {"?i?"}, {"?i*"}, {"???"}, {"?"}, {"*"}, {"****"}, {"o?*"}, 
                      {"jump"}, {"window?"}, {"window*"}, {"*window*"},{""} };
 
 vector<string> wm;
 
 if( argc==1) cout<<"\nUsage: $> pattmatch 'pattern' ['input_string']\n\n";
 if( argc>=2){ patt.clear(); patt.push_back( argv[1]); }
 if( argc==3) input=argv[2];

 for( int p=0; p< patt.size(); p++){
 
     wm= match( input, patt[p]);
     
     // output:
     cout<< "input: "<< input<<endl <<" pattern: "<< patt[p]<< endl << " matches: ";
     for( int i=0; i<wm.size(); i++){
         cout<< wm[i]; if( i!=wm.size()-1 ) cout<<',';
     }        
     cout<<"\n\n";
 }    
 
 return(0);
}




