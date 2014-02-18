public class CardNumberChecker {

  public static void main ( String args[] ) {
    if ( check( args[0] ) ) {
      System.out.println( "valid" );
    }
    else {
      System.out.println( "invalid" );
    }
  }

  public static boolean check ( String number ) {
    byte[] digits = new byte[ number.length() ];
    for ( int i = 0; i < digits.length; i++ ) {
      digits[i] = Byte.parseByte( "" + number.charAt(i) );
    }
    for ( int i = number.length() - 2; i >= 0; i -= 2 ) {
      digits[i] = dubSum (digits[i]);
    }
    byte sum = (byte)0;
    for ( int i = 0; i < digits.length; i++ ) {
      sum += digits[i];
      sum %= (byte)10;
    }
    return (sum == (byte)0);
  }
  
  private static byte dubSum ( byte input ) {
    switch ( input ) {
      case (byte) 0:
      return 0;
      case (byte) 1:
      return 2;
      case (byte) 2:
      return 4;
      case (byte) 3:
      return 6;
      case (byte) 4:
      return 8;
      case (byte) 5:
      return 1;
      case (byte) 6:
      return 3;
      case (byte) 7:
      return 5;
      case (byte) 8:
      return 7;
      case (byte) 9:
      return 9;
    }
    return 99;
  }
  
}