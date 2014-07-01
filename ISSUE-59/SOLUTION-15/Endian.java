import java.nio.ByteOrder;

public class Endian {
	public static void main(String argv[]) {
		ByteOrder b = ByteOrder.nativeOrder();
		if (b.equals(ByteOrder.BIG_ENDIAN)) {
			System.out.println("Big-endian");
		} else {
			System.out.println("Little-endian");
		}
	}
} 
