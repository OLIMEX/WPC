// theWylieStCoyote
// There is a error for steps greater then 190
#include <iostream>

using namespace std;

typedef unsigned long long ull;

ull permut(ull n, ull r)      //permutations
{
    ull out = 1;
    for(ull i = r; i <= n; i++)
    {
        out = out*i;
        if(out < i)
            cout << "___________\nERROR Answer invalid\n____________" << endl;
    }
    return out;
}

ull pwr(ull n, ull r, ull p)    //permutation with repition, total number of elements, no element 1, no element 2
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

ull pospaths(ull steps)         // calculates the total number of paths
{
    ull psc = ((steps << 1) >> 2) + 1;    // combinations of 1's and 2's that add to n steps
    ull no1s = steps;                     // number of 1's, The case of 1,1,...,1 has no possible combintations other then 1,1,...,1
    ull no2s = 0;                         // number of 2's
    ull pps = 0;                          // number of possible paths

    for(ull i = 0 ; i<psc; i++){
        no1s = steps - 2*i;
        no2s = i;
        pps = pps + pwr(no1s+no2s,no1s,no2s);
    }
    return pps;
}

int main()
{
    ull steps;    //number of steps
    cout << "Enter the number of steps: ";
    cin >> steps;
    cout << "The number of possible combinations of steps are: " << pospaths(steps) << endl;
    return 0;
}
