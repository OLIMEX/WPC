//compile:g++ -o  PTClinearization  PTClinearization.cpp
//run:./PTClinearization


#include <iostream>

using namespace std;

int main()
{
    int data [24][3] = {
    { -55 ,  475 ,  505 } ,
    { -50 , 500  ,  530 } ,
    { -40 , 552  ,  582 } ,
    { -30 , 609  ,  638 } ,
    { -20 , 669  ,  698 } ,
    { -10 , 733  ,  761 } ,
    {   0 , 802  ,  828 } ,
    {  10 , 874  ,  898 } ,
    {  20 , 950  ,  972 } ,
    {  25 , 990  , 1010 } ,
    {  30 ,1029  , 1051 } ,
    {  40 ,1108  , 1136 } ,
    {  50 ,1192  , 1225 } ,
    {  60 ,1278  , 1319 } ,
    {  70 ,1369  , 1416 } ,
    {  80 ,1462  , 1518 } ,
    {  90 ,1559  , 1623 } ,
    { 100 ,1659  , 1733 } ,
    { 110 ,1762  , 1847 } ,
    { 120 ,1867  , 1963 } ,
    { 125 ,1919  , 2020 } ,
    { 130 ,1970  , 2077 } ,
    { 140 ,2065  , 2184 } ,
    { 150 ,2145  , 2277 }

    } ;

    cout << "number of resistance in ohms: " ;
    int r ;
    cin >> r ;
    for ( int i=0 ; i < 24 ; i++)
        if ( r >= data[i][1] &&  r <= data[i][2] ) {
            cout << "temperature is" << data[i][0] << endl ;
            return 0 ;
        }


    cout << "no info " << endl ;

    return 0;
}
