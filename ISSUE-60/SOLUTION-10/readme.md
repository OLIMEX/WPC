Hello,
my solution uses polynomial interpolation to approximate the table from
data sheet.

the code is in Java  but extremly simple to write in C for small
microcontrollers

public class KTY81_110 {
/**
* Aproximate PTC KTY81-110 resistence/temperaure table (table 7 of data
sheet)
* 490, -55 * 515, -50 * 567, -40 * 624, -30 * 684, -20 * 747, -10 * 815, 0
* 886, 10 * 961, 20 * 1000, 25 * 1040, 30 * 1122, 40 * 1209, 50 * 1299, 60
* 1392, 70 * 1490, 80 * 1591, 90 * 1696, 100 * 1805, 110 * 1915, 120 *
1970, 125 * 2023, 130 * 2124, 140 * 2211, 150
* with 5th degree polynomial. Coefficients are calculated with least square
fitting
* algorithm. You can do that using Maxima or other mathematical tools. For
this
* example I used the online tool available at http://www.xuru.org/rt/PR.asp
* The maximum error is about 0.12 °C
* With e 4th degree polynomial maximum error is about 0.6 °C
* With 9 multiplications and 5 sums I do the conversion from Ohm to °C
 */
public static double temperature(double resistence) {
 // in order to optimize the number of floating point multiplication on
small
 // microcontrollers (not for Java)
 double r2 = resistence * resistence;
 double r3 = r2 * resistence;
 double r4 = r3 * resistence;
 double r5 = r4 * resistence;
return
  1.588560974e-14 * r5
  - 1.077078151e-10 * r4
  + 2.969300166e-7 * r3
  - 4.399145663e-4 * r2
  + 4.672892621e-1 * resistence
  - 207.5343491;
}
}


*x*
*y*

*Calculated y*

*Error*
1.    -55.01299051   1.299050631·10-2 2.    -49.99992707   7.293342979·10-5
3.    -40.08458788   8.458787635·10-2 4.    -29.91984054   8.015946363·10-2
5.    -19.90123219   9.87678062·10-2 6.    -10.01789225   1.789225285·10-2
7.    3.715984314·10-2   3.715984314·10-2 8.    9.970996852   2.900314781·10
-2 9.    19.94403938   5.596062271·10-2 10.    24.94815806   5.184193922·10
-2 11.    29.96513862   3.486138176·10-2 12.    39.91947291   8.052708785·10
-2 13.    50.04434636   4.434636042·10-2 14.    60.08989772   8.989772129·10
-2 15.    70.04354871   4.354871047·10-2 16.    80.09021693   9.021692719·10
-2 17.    90.00722492   7.224924939·10-3 18.    99.91704538   8.295462421·10
-2 19.    109.9094937   9.05062531·10-2 20.    119.924439   7.556102615·10-2
 21.    125.0137229   1.372290024·10-2 22.    130.0407169   4.071694239·10-2
 23.    140.1898523   1.898523262·10-1 24.    149.8809995   1.190004944·10-1



Carlo Amaglio


