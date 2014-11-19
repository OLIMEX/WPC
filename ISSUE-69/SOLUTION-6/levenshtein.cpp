#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
uint32_t levenshtein_distance( T& s1, T& s2)
{
	size_t len1 = s1.size(), len2 = s2.size();
	vector<vector<uint32_t> > d(len1 + 1, vector<uint32_t>(len2 + 1));

	for(size_t i = 1; i <= len1; ++i) d[i][0] = i;
	for(size_t i = 1; i <= len2; ++i) d[0][i] = i;

    d[0][0] = 0;
	for(size_t i = 1; i <= len1; ++i)
		for(size_t j = 1; j <= len2; ++j)
            d[i][j] = min( min(d[i - 1][j] + 1,d[i][j - 1] + 1),
                            d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) );
	return d[len1][len2];
}


int main()
{
    string wordA , wordB ;
    cout << "input first string " ;
    cin >> wordA ;
    cout << "input second string " ;
    cin >> wordB ;
    cout << wordA << "," << wordB << endl;
    uint32_t d = levenshtein_distance ( wordA , wordB);
    cout << "levenshtein_distance [" << d << "]" << endl ;
    return 0;
}

