
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;
import java.nio.charset.Charset;
import java.util.Arrays;
import java.util.HashSet;
import java.util.regex.Pattern;

/**
 * Must be compiled with a java 7 compiler.
 *
 * Usage: java Similar [ local-file.txt | http-url.html ] word ...
 *
 * Finds all similar words to those listed in the source file
 * and prints them out.
 * 
 * The html loader ignores tags, but not <script> or other html content so
 * may report false results; but possibly not with this text.
 * 
 * - NotZed
 */
public class Similar {

	static String[] scan2(BufferedReader br, Pattern pattern, boolean html) throws IOException {
		StringBuilder sb = new StringBuilder();
		HashSet<String> matches = new HashSet<>();
		int state = 0;
		int htmlstate = 0;
		int ch;
		
		/**
		 * Splits input into words and then runs the pattern against
		 * each one.
		 * Ignores html tags in html mode.
		 */

		while ((ch = br.read()) != -1) {
			ch = Character.toLowerCase(ch);
			switch (state) {
				case 0:
					if (Character.isAlphabetic(ch)) {
						sb.append((char) ch);
					} else if (ch == '\'') {
						state = 2;
					} else {
						if (pattern.matcher(sb).matches()) {
							matches.add(sb.toString());
						}
						sb.setLength(0);
						if (ch == '<' && html) {
							state = 1;
							htmlstate = 0;
						}
					}
					break;
				case 1:
					if (ch == '>')
						state = htmlstate;
					break;
				case 2:
					// Handle potential apostraphe
					if (Character.isAlphabetic(ch)) {
						sb.append('\'');
						sb.append((char) ch);
						state = 0;
					} else if (ch == '<' && html) {
						state = 1;
						htmlstate = 2;
					} else {
						if (pattern.matcher(sb).matches()) {
							matches.add(sb.toString());
						}
						sb.setLength(0);
						state = 0;
						if (ch == '<' && html)
							state = 1;
					}
					break;
			}
		}
		return matches.toArray(new String[matches.size()]);
	}

	static BufferedReader open(String path) throws MalformedURLException, IOException {
		if (path.toLowerCase().startsWith("http:"))
			return new BufferedReader(
					new InputStreamReader(
					new URL(path).openStream(),
					Charset.forName("utf-8")));
		else
			return new BufferedReader(new FileReader(path));
	}

	public static void main(String[] args) {
		if (args.length < 2) {
			System.out.printf("Usage: [ input.txt | http://host/input.html ] word ...");
			System.exit(1);
		}

		String path = args[0];

		// Build regex for each possibility:
		// 1 letter changed
		// 1 letter inserted
		// 1 letter deleted
		StringBuilder regex = new StringBuilder();
		regex.append("^(");
		for (int w = 1; w < args.length; w++) {
			String word = args[w];
			// replace any position with .
			regex.append(word);
			for (int i = 0; i < word.length(); i++) {
				regex.append("|");
				for (int j = 0; j < word.length(); j++) {
					if (i == j)
						regex.append('.');
					else
						regex.append(word.charAt(j));
				}
			}
			// Insert at any position
			for (int i = 0; i < word.length(); i++) {
				regex.append("|");
				for (int j = 0; j < word.length(); j++) {
					if (i == j)
						regex.append('.');
					regex.append(word.charAt(j));
				}
			}
			// end position
			regex.append("|");
			regex.append(word);
			regex.append('.');
			// Delete at any position
			for (int i = 0; i < word.length(); i++) {
				regex.append("|");
				for (int j = 0; j < word.length(); j++) {
					if (i != j)
						regex.append(word.charAt(j));
				}
			}
		}
		regex.append(")$");

		System.err.println("Using regex: " + regex);
		Pattern pattern = Pattern.compile(regex.toString(), Pattern.CASE_INSENSITIVE);

		System.err.println("Loading: " + path);

		try (BufferedReader br = open(path)) {
			boolean html = path.toLowerCase().startsWith("http:");
			String[] words = scan2(br, pattern, html);

			Arrays.sort(words);

			if (words.length == 0)
				System.err.println("No matches");
			else {
				System.err.printf("There were %d matche(s):\n", words.length);
				for (String best : words)
					System.out.println(" " + best);
			}
		} catch (MalformedURLException ex) {
			System.out.println("URL cannot be parsed: " + path);
		} catch (IOException ex) {
			System.out.println("IO Error: " + ex.getLocalizedMessage());
		}
	}
}
