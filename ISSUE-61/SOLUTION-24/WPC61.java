package test.contest;

import java.util.LinkedList;

/**
 * 
 * License: LGPL
 * OLIMEX WPC#61: plus minus
 * 
 * Problem:
 * insert + and – in the equation below to make it right
 * 1 2 3 4 5 6 7 8 9 = 100
 * like
 * 1 + 2 + 3 – 4 + 5 + 6 + 7 8 + 9 = 100
 * make code which  finds all solutions.
 * 
 * 
 * @author Dott. Ing. Carlo Amaglio - BMB S.p.A. - Via Enrico Roselli, 12 - 25125 Brescia<p>
 *
 */
public class WPC61 {

	static final boolean DEBUG = false;

	static LinkedList<String> check(String[] numbers, int result) {
		LinkedList<String> rv = new LinkedList<String>();
		char[] operators = new char[numbers.length];
		for (int i=0; i<operators.length; i++) operators[i]=' ';
		do {
			int v = eval(numbers, operators);
			if (v == result || v == -result) {
				rv.add(expr(numbers, operators, v == -result) + " = " + result);
			}
		} while (next(operators));
		return rv;
	}

	static boolean next(char[] operators) {
		for (int i=operators.length-1; i>0; i--) {
			switch (operators[i]) {
				case ' ': operators[i]='+'; return true;
				case '+': operators[i]='-'; return true;
				case '-': operators[i]=' '; break;
			}
		}
		return false;
	}

	static int eval(String[] numbers, char[] operators) {
		int rv = 0;
		String n = "";
		if (DEBUG) System.out.println("-------------------");
		for (int i=0; i<operators.length; i++) {
			if (operators[i]==' ') n+=numbers[i];
			else {
				if (DEBUG) System.out.println(n);
				rv += Integer.valueOf(n);
				n = (operators[i]=='-' ? "-":"") + numbers[i];
			}
		}
		rv += Integer.valueOf(n);
		return rv;
	}

	static String expr(String[] numbers, char[] operators, boolean chs) {
		String rv = "";
		String n = chs ? "-" : "";
		for (int i=0; i<operators.length; i++) {
			if (operators[i]==' ') n+=numbers[i];
			else {
				rv += n;
				n = (chs ? (operators[i]=='+'?'-':'+') : operators[i]) + numbers[i];
			}
		}
		rv += n;
		return rv;
	}

	public static void main(String[] args) {
		LinkedList<String> l = check(new String[] { "1", "2", "3", "4", "5", "6", "7", "8", "9" }, 100);
		for (String s : l) {
			System.out.println(s);
		}
	}
}
