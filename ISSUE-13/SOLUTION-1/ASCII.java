
import java.awt.Color;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.BitSet;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;

/**
 * Olimex WPC # 13 - Convert an image to ASCII.
 *
 * Basic approach is to create a bitmap of a given font and then match
 * each correspondingly sizes output cell to the font glyphs
 * using least-squared-error.
 * 
 * output.txt is an example of 8-bit output (iso-8859-1 encoding)
 * output-ascii.txt is an example for 7-bit output.
 *
 * Defaults to using the iso-8859-1, but can be forced to ascii (see
 * --ascii option).
 *
 * Gamma correction helps with some images. Getting the correct font compared
 * to the output font helps, although java's idea of font sizes differs from
 * gtk+'s (see -t option). Black-on-white or white-on-black output is
 * supported (see --invert option).
 *
 * See usage() for all of the arguments.
 *
 * Example for 160+ column terminal:
 * java ASCII -w 160 -g 1.5 lenna.jpg logo.png
 * For a terminal with black background and light text:
 * java ASCII --invert -w 160 -g 1.1 lenna.jpg logo.png
 *
 * Force ASCII-only output.
 * java ASCII -w 160 -g 1.5 --ascii lenna.jpg logo.png
 *
 * - notzed
 *
 * Code in public domain.
 */
public class ASCII {

	int fwidth, fheight;
	// This may be increased for e.g. cjk fonts, but don't expect performance.
	// must be even multiple of ncols
	final int nchars = 256;
	final int ncols = 16;
	final int nrows = nchars / ncols;
	float[] characters;
	BitSet ignore = new BitSet(nchars);
	float[] gammalut = new float[256];
	boolean invert = false;
	String dump = null;
	String dumpTable = null;
	// Create image for every font letter

	public ASCII(boolean ascii) {
		// special/ control chars
		for (int i = 0; i < 32; i++) {
			ignore.set(i);
			ignore.set(i + 128);
		}
		ignore.set(127);

		// For 7-bit ascii ignore 8 bit values
		if (ascii)
			for (int i = 128; i < 256; i++)
				ignore.set(i);


		for (int i = 0; i < gammalut.length; i++)
			gammalut[i] = i;
	}

	void setDump(String name) {
		dump = name;
	}

	void setDumpTable(String name) {
		dumpTable = name;
	}

	void setInvert(boolean invert) {
		this.invert = invert;
	}

	void setGamma(double g) {
		for (int i = 0; i < gammalut.length; i++)
			gammalut[i] = (float) Math.pow(i / 255.0, 1 / g) * 255;
	}

	void loadFont(String name) {
		Font font = Font.decode(name);

		// Dummy image just to get font metrics
		BufferedImage letters = new BufferedImage(1, 1, BufferedImage.TYPE_BYTE_GRAY);
		Graphics2D gg = letters.createGraphics();
		FontMetrics fm = gg.getFontMetrics(font);
		int ascent = fm.getAscent() + fm.getLeading();

		fheight = fm.getHeight();
		fwidth = fm.getWidths()[(int) 'm'];

		//System.out.printf("font size is %dx%d\n", fwidth, fheight);

		int width = fwidth * ncols;
		int height = fheight * nrows;

		letters = new BufferedImage(width, height, BufferedImage.TYPE_BYTE_GRAY);

		gg = letters.createGraphics();
		gg.setFont(font);
		gg.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_ON);

		if (invert) {
			gg.setBackground(Color.black);
			gg.setColor(Color.white);
		} else {
			gg.setBackground(Color.white);
			gg.setColor(Color.black);
		}

		gg.clearRect(0, 0, width, height);

		// Draw characters
		char[] chars = new char[1];
		for (int y = 0; y < nrows; y++) {
			for (int x = 0; x < ncols; x++) {
				int cp = y * nrows + x;

				if (!ignore.get(cp)) {
					chars[0] = (char) (cp);
					String s = new String(chars);
					gg.drawString(s, x * fwidth, y * fheight + ascent);
				}
			}
		}

		// debug: dump font image
		if (dumpTable != null) {
			try {
				ImageIO.write(letters, "png", new File(dump));
			} catch (IOException ex) {
				Logger.getLogger(ASCII.class.getName()).log(Level.SEVERE, null, ex);
			}
		}

		// Flatten array, pre-convert to float
		characters = new float[fwidth * nchars * fheight];
		byte[] pixels = new byte[width * height];
		letters.getRaster().getDataElements(0, 0, width, height, pixels);
		for (int y = 0; y < nrows; y++) {
			for (int x = 0; x < ncols; x++) {
				int op = (x + y * ncols) * fwidth * fheight;
				for (int j = 0; j < fheight; j++) {
					for (int i = 0; i < fwidth; i++) {
						characters[op + i + j * fwidth] = (pixels[x * fwidth + i + (y * fheight + j) * width] & 0xff);
					}
				}
			}
		}
	}

	/**
	 * Match a grid of pixels to a character using least square error
	 */
	int matchCell(float[] cell, int size, float[] tests, int ntests) {
		int besti = 0;
		float bestv = Float.MAX_VALUE;

		for (int i = 0; i < ntests; i++) {
			if (!ignore.get(i)) {
				float v = 0;
				for (int j = 0; j < size; j++) {
					float e = cell[j] - tests[i * size + j];
					v += e * e;
				}

				if (v < bestv) {
					bestv = v;
					besti = i;
				}
			}
		}
		return besti;
	}

	/**
	 * Main routine - scales image and then converts it to ASCII.
	 */
	void convertImage(BufferedImage src, int cols, int rows, double gamma) {
		// Create an image which matches the font size
		int width = fwidth * cols;
		int height = fheight * rows;

		BufferedImage scaled = new BufferedImage(width, height, BufferedImage.TYPE_BYTE_GRAY);
		Graphics2D gg = scaled.createGraphics();

		gg.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
		gg.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BICUBIC);

		// clear first for alpha-blended
		gg.setBackground(Color.white);
		gg.clearRect(0, 0, width, height);

		// This doesn't downsample properly but is 'good enough'
		gg.drawImage(src, 0, 0, width, height, 0, 0, src.getWidth(), src.getHeight(), null);
		gg.dispose();

		// Convert to float & gamma correct
		float[] pixels = new float[width * height];

		if (gamma == 1) {
			scaled.getRaster().getPixels(0, 0, width, height, pixels);
		} else {
			byte[] bpixels = new byte[width * height];

			setGamma(gamma);
			scaled.getRaster().getDataElements(0, 0, width, height, bpixels);

			for (int i = 0; i < bpixels.length; i++) {
				pixels[i] = gammalut[bpixels[i] & 0xff];
			}

			scaled.getRaster().setPixels(0, 0, width, height, pixels);
		}

		if (dump != null) {
			try {
				ImageIO.write(scaled, "png", new File(dump));
			} catch (IOException ex) {
				Logger.getLogger(ASCII.class.getName()).log(Level.SEVERE, null, ex);
			}
		}

		// Now convert each character by finding the closest match using sum squared error
		float[] cell = new float[fwidth * fheight];
		for (int y = 0; y < rows; y++) {
			for (int x = 0; x < cols; x++) {
				// Extract cell
				for (int j = 0; j < fheight; j++) {
					for (int i = 0; i < fwidth; i++) {
						cell[i + j * fwidth] = pixels[x * fwidth + i + (y * fheight + j) * width];
					}
				}
				// find closest match
				int c = matchCell(cell, fwidth * fheight, characters, nchars);

				System.out.print((char) c);
			}
			System.out.println();
		}
	}

	static void usage() {
		System.out.println("Usage: ASCII [--ascii] [-w width] [-h height] [-f font] [-g gamma] images ...");
		System.out.println("  --ascii    Force 7-bit ascii (default: 8 bit of system)");
		System.out.println("  --invert   Use white-on-black characters.  Defaults to black-on-white.");
		System.out.println("  -w width   Output width in characters");
		System.out.println("  -h height  Output height in rows.");
		System.out.println("               If width or height not specified one is estimated from the other");
		System.out.println("  -f font    Font to use for error measurement, java format (default Monospaced-13)");
		System.out.println("               This should be a monospaced typeface.");
		System.out.println("  -g gamma   Gamma correction factor (default 1.0)");
		System.out.println("  -t out.png Dump table of letterforms used to specified file");
		System.out.println("  -d out.png Dump scaled image used for generation");
	}

	public static void main(String[] args) {
		// This is an 8x15 font in pixels
		String font = "Monospaced-13";
		int w = -1;
		int h = -1;
		boolean ascii = false;
		List<String> srcs = new ArrayList<>();
		double gamma = 1;
		boolean invert = false;
		String dump = null;
		String dumpTable = null;

		for (int i = 0; i < args.length; i++) {
			switch (args[i]) {
				case "--ascii":
					ascii = true;
					break;
				case "--invert":
					invert = true;
					break;
				case "-w":
					w = Integer.valueOf(args[++i]);
					break;
				case "-h":
					h = Integer.valueOf(args[++i]);
					break;
				case "-f":
					font = (args[++i]);
					break;
				case "-g":
					gamma = Double.valueOf(args[++i]);
					break;
				case "-d":
					dump = (args[++i]);
					break;
				case "-t":
					dumpTable = (args[++i]);
					break;
				default:
					srcs.add(args[i]);
					break;
			}
		}

		if (srcs.isEmpty()) {
			usage();
			return;
		}

		if (w == -1 && h == -1) {
			w = 80 * 2;
		}

		ASCII a = new ASCII(ascii);

		a.setInvert(invert);
		a.setDump(dump);
		a.setDumpTable(dumpTable);

		a.loadFont(font);

		for (String name : srcs) {
			try {
				BufferedImage src = ImageIO.read(new File(name));
				int ow = w, oh = h;

				if (h == -1) {
					oh = src.getHeight() * w / src.getWidth();
					// for the font
					oh = oh * 8 / 15;
				}
				if (w == -1) {
					ow = src.getWidth() * h / src.getHeight();
					ow = ow * 15 / 8;
				}

				a.convertImage(src, ow, oh, gamma);
			} catch (IOException ex) {
				System.err.printf("Unable to load: %s: %s\n", name, ex.getLocalizedMessage());
			}
		}
	}
}
