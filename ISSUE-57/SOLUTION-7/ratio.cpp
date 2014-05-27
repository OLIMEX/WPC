// use the libcurl library in C++. 
// for install ubuntu use libcurl4-openssl-dev or libcurl4-gnutls-dev.
// for complle and link: g++ -Wall ratio.cpp `pkg-config --cflags --libs libcurl` -o ratio
// for run:./ratio URL


#include <string>
#include <iostream>
#include <curl/curl.h>

using namespace std;

string contents;

size_t handle_data(void *ptr, size_t size, size_t nmemb, void *stream)
    {
    int numbytes = size*nmemb;
    char lastchar = *((char *) ptr + numbytes - 1);
    *((char *) ptr + numbytes - 1) = '\0';
    contents.append((char *)ptr);
    contents.append(1,lastchar);
    *((char *) ptr + numbytes - 1) = lastchar;  
    return size*nmemb;
    }

int main(int argc, char *argv[])
    {
    if (argc != 2)
        {
        cerr << "use:./ratio url" << endl ;
        return -1;
        }

    CURL* curl = curl_easy_init();
    if(curl)
        {
        curl_easy_setopt(curl,CURLOPT_URL, argv[1]);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,handle_data);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if (res != 0)
            cerr << "Error: " << res << endl;
        }

	int f_ , s_ , t_ , n_;  
	s_ = contents.size() ;
	f_ = t_ = n_ = 0 ;
        while ( f_ > -1) {
		f_ = contents.find("title", f_);
		if ( f_ > 0 ) {
			int b_ = f_++ ;
			int e_ = contents.find("/title", f_);
			if ( e_ > 0 ) 
				t_ = t_ + e_ - b_ ;
			if ( n_ <= 0 ) 
				n_ = contents.find("301 Moved Permanently", f_);	
			f_+= 2;				

		}
	}	

	double ratio   ;
	ratio =  t_ / (s_ / 100.00)   ;
	if ( n_ > 0 ) 
		cout << "maybe can't calculate ratio correct  , https connection " << endl ;
	cout << "ratio = " << ratio << endl ;
    return 0;
    }  
