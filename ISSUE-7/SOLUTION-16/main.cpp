// theWylieStCoyote
// There is a error for steps greater then 94
#include <iostream>

using namespace std;

unsigned long permut(unsigned long n, unsigned long r)      //permutations
{
    unsigned long out = 1;
    for(unsigned long i = r; i <= n; i++)
    {
        out = out*i;
    }
    return out;
}

unsigned long pwr(unsigned long n, unsigned long r, unsigned long p)    //permutation with repition, total number of elements, no element 1, no element 2
{
    if((n==r)||(n==p))
    {
        return 1;
    }
    else if(r == p)
    {
        return permut(n,r+1)/permut(r,1);
    }
    else if(r>p)
    {
        return permut(n,r+1)/permut(p,1);
    }
    else if(p>r)
    {
        return permut(n,p+1)/permut(r,1);
    }
    else
    {
        cout << "ERROR!" << endl;
        return 0;
    }
}

unsigned long pospaths(unsigned long steps)         // calculates the total number of paths
{
    unsigned long psc = ((steps << 1) >> 2) + 1;    // combinations of 1's and 2's that add to n steps
    unsigned long no1s = steps;                     // number of 1's, The case of 1,1,...,1 has no possible combintations other then 1,1,...,1
    unsigned long no2s = 0;                         // number of 2's
    unsigned long pps = 0;                          // number of possible paths

    for(unsigned long i = 0 ; i<psc; i++){
        no1s = steps - 2*i;
        no2s = i;
        pps = pps + pwr(no1s+no2s,no1s,no2s);
    }
    return pps;
}

int main()
{
    unsigned long steps;    //number of steps
    cout << "Enter the number of steps: ";
    cin >> steps;
    cout << "The number of possible combinations of steps are: " << pospaths(steps) << endl;
    return 0;
}
