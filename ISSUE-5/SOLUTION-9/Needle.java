package zarev.wpc;

import java.util.Random;
import java.util.Scanner;

public class Needle {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		double len = 0.0, width = 0.0;
		int needles = 0;

		System.out.print("Needle length: ");
		len = in.nextDouble();
		if (len <= 0) {
			System.err.println("The needle length must be positive");
			System.exit(0);
		}
		System.out.print("Stripes width: ");

		width = in.nextDouble();
		if (width <= 0) {
			System.err.println("The stripes width must be positive");
			System.exit(0);
		}

		if (width < len) {
			System.err.println("The stripes width must be greater or equal than the needles length");
			System.exit(0);
		}

		System.out.print("Number of needles: ");
		needles = in.nextInt();
		if (needles <= 0) {
			System.err.println("The number of needles must be positive");
			System.exit(0);
		}

		Random random = new Random();
		int crossing = 0;
		double halfLen = len / 2;
		double halfWidth = width / 2;

		for (int i = 0; i < needles; i++) {
			double distance = random.nextDouble() * halfWidth;
			double angle = random.nextDouble() * Math.PI;

			if (distance <= halfLen * Math.sin(angle)) {
				crossing++;
			}
		}

		if (0 < crossing) {
			double pi = (2 * len * needles) / (width * crossing);
			System.out.println("PI:\t" + pi);
		} else {
			System.out.println("Cannot estimate PI");
		}
	}

}
