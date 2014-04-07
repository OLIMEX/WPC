
#include <stdio.h>

bool add13Days(unsigned short year, unsigned short *month, unsigned int *day)
{
    unsigned short monthlen[]={31,28,31,30,31,30,31,31,30,31,30,31};
    int newDay;
    if ((*day + 13) > monthlen[(*month) - 1])
    {
        newDay = *day + 14 - monthlen[(*month)];
        (*month) ++;
    }
    else
    {
        newDay = *day + 13;
    }
    *day = newDay;

}

//check if date exists in human's calendar
bool isDateValid(unsigned short year, unsigned short month, unsigned int day)
{
    unsigned short monthlen[]={31,28,31,30,31,30,31,31,30,31,30,31};
    //dates before 1583 are not compatible with Gregorian (Wester Christian) calenar.
    if( year <= 1582)
        return false;
    if(!(year%4) && (year%100) || !(year%400))
    {
        monthlen[1] = 29;
        printf("Leap year/r/n");
    }
    if (day>monthlen[month-1])
        return false;
    return true;
}

//Practical Astronomy With Your Calculator, 2nd Edition by Peter Duffett-Smith
bool easterGregDate(const unsigned short year, unsigned short * month, unsigned int * day)
{
    unsigned short a, b, c, d, e, f, g, h, i, k, l, m, p;
    a=year%19;
    b=year/100;
    c=year%100;
    d=b/4;
    e=b%4;
    f=(b+8)/25;
    g=(b-f+1)/3;
    h=(19*a+b-d-g+15)%30;
    i=c/4;
    k=c%4;
    l=(32+2*e+2*i-h-k)%7;
    m=(a+11*h+22*l)/451;
    *month =(h+l-7*m+114)/31;  //[3=March, 4=April]
    p=(h+l-7*m+114)%31;
    *day =p+1; //     (date in Easter Month)
    return true;
}

bool easterJulianDate(const unsigned short year, unsigned short * month, unsigned int * day)
{
    unsigned short  a, b, c, d, e;

    a = year % 4;
    b = year % 7;
    c = year % 19;
    d = (19 * c + 15) % 30;
    e = 2 * a;
    e += 4 * b;
    e = e - d + 34;
    e = e % 7;
    *month = ( d + e + 114) / 31;
    *day = 1 + (d + e + 114) % 31;
}

int main(int argc, char *argv[])
{
    unsigned short Mon;
    unsigned int Day;


    //usage example to compare with wikipedia's table
    for (int j = 0; j<40; j++)
    {
        easterGregDate(1994+j, &Mon, &Day);
        if (false == isDateValid(2014, Mon, Day))
            printf("WRONG NUMBER; WRONG CALCULATED!/r/n");
        printf("A.D.%d Gregorian Easter@ Month=%d Day=%d  ",1994+j, Mon, Day);
        easterJulianDate(1994+j, &Mon, &Day);
        add13Days(1994+j, &Mon, &Day);
        if (false == isDateValid(2014, Mon, Day))
            printf("WRONG NUMBER; WRONG CALCULATED!/r/n");
        printf("Orthodox Easter in Gregorian calendar@ Mon=%d Day=%d\r\n", Mon, Day);
    }
    return 0;
}
