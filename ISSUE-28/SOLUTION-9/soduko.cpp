// compile & link : g++ -o soduko soduko.cpp
// for run: ./soduko < in.txt

#include <iostream>

using namespace std ;

static const int lim = 9 ;

int main()
{
	int f[lim][lim],init[lim][lim];
	int i , j , i1 , j1 ;
	int flag;

	for(i=0 ; i<lim ;i++)
        for(j=0 ; j<lim ;j++) {

		cin>>init[i][j];
		f[i][j]=init[i][j];
	}
	cout<<"input matrix:" << endl ;
	for( i=0 ; i<lim ;i++)
	{
		for( j=0; j<lim; j++)
			cout << f[i][j] << " ";
		cout << endl ;
	}

    // check input data
	for( i=0 ; i < lim ; i++ )
        for( j=0 ; j<lim ; j++)
        {
            if(f[i][j] == 0 ) continue;
            flag = 0;
            for( i1=0 ; i1<lim ;i1++)
                if(i !=i1 && f[i][j] == f[i1][j] )
                    flag = 1;

            for( j1=0 ; j1 < lim ; j1++)
                if(j != j1 && f[i][j]==f[i][j1])
                    flag = 1;

            for( i1=0 ; i1<lim ;i1++ )
                for(j1=0; j1<lim ; j1++)
                    if(( i != i1 || j != j1) && i/3 == i1/3 && j/3 == j1/3 && f[i][j] == f[i1][j1] )
                        flag = 1;
            if(flag) {
                cout<<"input matrix error!!!  a number has been repeated" << endl ;
                return 1;
            }
        }

    // make decision
	for( i=0 ; i<lim; i++)
        for( j=0; j<lim; j++){
            if( init[i][j] >0 ) {
                if(i == lim-1 && j==lim-1 )  {
                    cout<<"decision: "<<endl;
                    for( i1=0 ; i1<lim; i1++) {
                        for( j1=0 ; j1<lim ; j1++)
                            cout << f[i1][j1] << " ";
                    cout<<endl ;
                }
                return 1 ;
                }
                continue ;
            }

            for(f[i][j]++ ;f[i][j] <= lim ; f[i][j]++) {
                flag = 0;
                for( i1=0 ; i1 < lim ;i1++ )
                    if(i != i1 && f[i][j] == f [i1][j] ) flag = 1;
                for( j1=0 ; j1<lim ; j1++ )
                    if( j != j1 && f[i][j] == f[i][j1] ) flag = 1;
                for( i1=0 ; i1<lim; i1++)
                    for(j1=0;j1<9;j1++)
                        if(( i != i1 || j != j1) && i/3 == i1/3 && j/3 == j1/3 && f[i][j] == f[i1][j1])
                            flag=1;
                if(!flag )break;
            }
            if(f[i][j] > lim ) {
                f[i][j] = 0 ;
                do {
					if( i == 0 && j == 0 ) { cout << "no  decision" << endl ; return 1 ; }
                    if( j > 0) j--;
                    else {
                        j=lim-1;
                        i--;
                    }
                }while(init[i][j] > 0 );
                j--;
            }

            if( i==lim-1  && j == lim-1 ) {
                cout<<"decision: "<<endl;
                for( i1=0 ; i1<lim; i1++) {
                    for( j1=0 ; j1<lim ; j1++)
                        cout << f[i1][j1] << " ";
                    cout<<endl ;
                }
                return 1 ;
            }

	}  // end of double for
	cout<<"no decision" << endl ;
}


