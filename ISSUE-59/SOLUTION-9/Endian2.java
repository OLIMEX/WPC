import java.nio.*;
import java.nio.channels.*;
import java.io.*;
public class Endian2 {
	public static void main( String args[] ) {
		try {
			if ( isBigEndian() ) {
				System.out.println( "big" );
			}
			else {
				System.out.println( "little" );
			}
		}
		catch ( Exception e ) {
			e.printStackTrace();
		}
	}
	public static boolean isBigEndian () throws FileNotFoundException, IOException {
		int number = 1;//a number for testing puposes
		File testfile = new File( "justATestFile" );
		//write the number to a file java automagically uses correct endianness for pour System
		BufferedWriter writeToFile = new BufferedWriter( new OutputStreamWriter( new FileOutputStream( testfile ) ) );
		writeToFile.write( number );
		writeToFile.flush();
		writeToFile.close();
		//we read our number and force our buffer to treat it as big endian
		FileInputStream inStream = new FileInputStream( testfile );
		FileChannel inChannel = inStream.getChannel();
		ByteBuffer buffer = ByteBuffer.allocate( 4 );
		buffer.order( ByteOrder.BIG_ENDIAN );
		inChannel.read( buffer );
		inChannel.close();
		inStream.close();
		testfile.delete();
		return buffer.getInt( 0 ) == number;
	}
}
