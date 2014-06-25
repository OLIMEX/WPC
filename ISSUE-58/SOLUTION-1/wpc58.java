public class test {
 static long beginning;

public static void main(String[] args) {
beginning = JD(1,1,1); // Set your begninning date. 1,1,1 for the new
testiment.
//beginning = JD(1, 1, -18300000000L); Aprox date of the universe
18,3Billion
 System.out.println( (JD(15, 8, 1984) - beginning)*24*60*60 + " seconds" );
}
 static long JD(int d, int m, long y){
return (long) (367*y - Math.floor( 7*( y + Math.floor( (m+9)/12 ))/4 )
- Math.floor( 3*( Math.floor( (y + ( m-9 )/7 )/100 )+1 )/4 )
+ Math.floor( 275*m/9) + d);
}
}

