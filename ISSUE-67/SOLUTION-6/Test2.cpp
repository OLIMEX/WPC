#include <iostream>
#include <cmath>

using namespace std;



int main() {

	int a=0;
float test=1;
	float somme=0;
	float n=1;
	int page;



	while( test-a !=0){
		n++;
 test=(9808/n-(n-1)/2);
 a=floor(test);




	}

	cout<<"missing pages: "<<n<<" first missing page is page N° "<<test<<endl;

	 for(int j=1;j<(n+1);j++){


	 		 somme=test-1+j+somme;
	 		 page=test-1+j;
	 		cout<<"page N° "<<page<<" sum "<<somme<<endl;
	 	 }






}



