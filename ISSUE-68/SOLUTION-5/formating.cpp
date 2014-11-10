#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


using namespace std;

int main(int argc , char*argv[])
{
  ifstream fin ;
  vector <string> tx ;
  vector <string> lin ;
  string tmp ;
  size_t static const   len_line = 60 ;

  fin.open ( "alice.txt",ios::in) ;


  while ( !fin.eof() ) {
    fin >> tmp ;
    tx.push_back(tmp);
  }
  fin.close();
  size_t current_len = 0 , words_len;
  for ( size_t i=0;i<tx.size(); i++){
    if ( (current_len + tx[i].length()) <= len_line ) {
        lin.push_back(tx[i]) ;
        current_len += tx[i].length();
        ++current_len;
        words_len += tx[i].length();
    }else {
        size_t space_len = len_line - words_len;
        words_len = space_len / (lin.size() - 1) ;
        for ( size_t j=0 ; j < lin.size() ;j++) {
            if ( j == 0 )    {
                cout << setw( lin[j].length() ) << lin[j] ;
                continue ;
            }
            if ( j == (lin.size() -1)) {
                int l = words_len + ( space_len - (words_len * lin.size()));
                l += lin[j].length();
                cout << setw(l) << lin[j];
                cout << endl ;
                break ;
            }
            else {
                int l = words_len ;
                l += lin[j].length();
                cout << setw(l) << lin[j];
            }
        }
        lin.clear();
        current_len = 0 ;
        --i ;
    }
   }

  return 0;
}
