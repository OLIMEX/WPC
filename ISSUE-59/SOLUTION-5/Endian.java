import java.nio.*;
public class Endian {
	public static void main( String args[] ) {
		ByteOrder order = ByteOrder.nativeOrder();
		if ( order.equals ( ByteOrder.LITTLE_ENDIAN ) ) {
			System.out.println( "little" );
		}
		else {
			System.out.println( "big" );
		}
	}
}
