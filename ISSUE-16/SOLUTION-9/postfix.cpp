/* 2013-07-07 by kantal59
   For descriptions see the postfix.h.
*/

#include <vector>
#include <string>
#include "postfix.h"

using namespace std;

int main( int argc, char *argv[])
{

    vector<string> extest= { {"(10 + 20) / (30 - 40)"}, { "-2*pow(-1*8/4, sqrt(5*20))"}, {"sqrt( pow(2,8/2))"}, {"100/5/-4"} };
     
    if( argc!=2){
        cout<<"\nUsage: $> postfix ""math_expression""\n\n";
    }
    else{ extest.clear(); extest.push_back( argv[1]); }
    
    for( int i=0; i< extest.size(); i++){
        Postfix p( extest[i]);
        // p.setDebug( true); // you can uncomment it
        if( p.parsing() !=0 ) cout <<"-- parsing error\n";
        cout<< "input: "<<'"'<< extest[i]<<'"' << endl<< "postfix: " <<p <<endl<< "value: "<< p.evaluate()<< endl<<endl;
    }    

 return(0);
}
