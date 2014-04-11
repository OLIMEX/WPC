#include <iostream>

using namespace std;

int main()
{
    cout << "enter center circle [(0,0) down left corner] :" << endl;
    int x , y ;
    cin >> x >> y ;
    if ( x >=25 && x <= 75 && y >= 25 && y <= 75 )
        cout << "the circle is completely inside" << endl ;
    else
        cout << "the circle isn't completely inside" << endl ;
    return 0;
}
