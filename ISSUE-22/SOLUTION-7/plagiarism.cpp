// g++ -o plagiarism plagiarism.cpp
// ./plagiarism  bee.txt wasp.txt

#include <set>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


int main (int argc , char** argv)
{

   if ( argc < 3 ) {
     cout << "format: program file1 file2" << endl ;
     return 0 ;
   }
   set<string> setStr;
   string s ;
   int num_file1 = 0 , num_file2 = 0  , num_common = 0  ;

   ifstream _in1_(argv[1]); // input file 1

    if(!_in1_) {
      cout << "Cannot open " <<  argv[1] << endl ;
      return 1;
    }



   while ( true ) {
      if ( _in1_.eof() ) break ;
     _in1_ >> s ;
     setStr.insert(s);
     ++num_file1 ;
  }
  _in1_.close() ;
  cout << "number words " << argv[1] << " = " <<  num_file1 << endl ;


//  for (set<string>::const_iterator p = setStr.begin( );p != setStr.end( ); ++p)
//      cout << *p << endl;


  ifstream _in2_(argv[2]); // input file 2

  if(!_in2_) {
      cout << "Cannot open " <<  argv[2] << endl ;
      return 1;
  }

  set<string>::iterator p ;
  while ( true ) {
     if ( _in2_.eof() ) break ;
     _in2_ >> s ;
     ++num_file2 ;
     p = setStr.find(s);
     ++num_file1 ;
     if ( p != setStr.end()) ++num_common ;
  }
  _in2_.close() ;
  cout << "number words " << argv[2] << " = " <<  num_file2 << endl ;
  cout << "common words " << " = " <<  num_common << endl ;

  return 0;
}
