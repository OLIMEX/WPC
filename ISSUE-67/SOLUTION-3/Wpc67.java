
public class Wpc67 {

	private static final int TOTAL = 9808;
	
	public static void main(final String[] args) {
		for (int m = 1; m < TOTAL; ++m) {
			for (int n = m + 1; n < TOTAL; ++n) {
				if (n * (n+1) - m * (m+1) == 2*TOTAL) {
					System.out.println("Missing pages are numbered from " + (m+1) + " to " + n);
				}
			}
		}
	}
}
