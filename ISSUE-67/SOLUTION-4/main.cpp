// Mario Fux <fux@kde.org>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int firstPage, lastPage;
    firstPage = 0;
    lastPage = 0;
    for (int i = 1; i <= 9808; i++) {
        int sum = 0;
        for (int j = i; j <= 9808; j++) {
            sum += j;
            if (sum == 9808) {
                cout << "From page " << i << " up " <<  j-i << " pages." << endl;
                firstPage = i;
                lastPage = j;
            }
            if (sum > 9808) {
                break;
            }
        }
        if (lastPage != 0) {
            cout << "These are the missing pages respectively their page numbers:" << endl;
            for (int k = firstPage; k <= lastPage; k++) {
                cout << k << endl;
            }
            firstPage = lastPage = 0;

        }
    }
}