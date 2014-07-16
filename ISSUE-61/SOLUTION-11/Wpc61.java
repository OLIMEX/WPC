import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Basic solution for WPC61.
 * 
 * @author marius.staicu
 *
 */
public class Wpc61 {

	private final static String SRC = "123456789";
	
	private final static int RESULT = 100;
	
	private final static char[] OPS = {' ', '+', '-'};
	
	private final Set<String> solutions = new HashSet<String>();
	
	private int solutionCount = 0;
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new Wpc61().run();
	}
	
	private void run() {
		solve("");
	}
	
	private void solve(final String state) {
		if (state.length() >= 8) {
			return;
		}
		for (final char c : OPS) {
			evaluate(state + c);
		}
	}
	
	private void evaluate(final String state) {
		int previdx = 0;
		final List<String> eq = new ArrayList<String>();
		for (int i = 0; i < state.length(); ++i) {
			final char c = state.charAt(i);
			if (c != ' ') {
				eq.add(SRC.substring(previdx, i+1));
				eq.add(String.valueOf(c));
				previdx = i+1;
			}
		}
		eq.add(SRC.substring(previdx));
		int value = value(eq);
		if (value == RESULT) {
			if (!solutions.contains(state.trim())) {
				System.out.println(printSolution(eq, value));
				solutions.add(state.trim());
			}
		}
		solve(state);
	}
	
	private int value(final List<String> eq) {
		int result = 0;
		String token = "";
		int pos = 0;
		for (final String term : eq) {
			if (pos % 2 == 0) {
				if (pos > 0) {
					if (token.equals("+")) {
						result += Integer.parseInt(term);
					} else {
						result -= Integer.parseInt(term);
					}
				} else {
					result = Integer.parseInt(term);
				}
			}
			token = term;
			pos++;
		}
		return result;
	}
	
	private String printSolution(final List<String> eq, final int value) {
		solutionCount++;
		final StringBuilder sb = new StringBuilder(128);
		sb.append("Solution ").append(solutionCount).append(": ");
		for (final String term : eq) {
			sb.append(term).append(' ');
		}
		sb.append("= ").append(value);
		return sb.toString();
	}
}
