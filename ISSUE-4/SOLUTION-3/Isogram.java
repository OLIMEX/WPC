package zarev.isogram;

import java.io.File;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Isogram {
	private static boolean isIsogram(String s) {
		/*
		 * Export the contents of the string to an array
		 * and sort it. If there are two equal 
		 * neighboring array elements, then 
		 * the word is not an isogram.
		 */
		char[] ch = s.toCharArray();
		Arrays.sort(ch);

		for (int i = 1; i < ch.length; i++) {
			if(ch[i-1] == ch[i]){
				return false;
			}
		}
		return true;
	}

	public static void main(String[] args) {
		//long start = System.currentTimeMillis();
		
		if (null == args || 1 != args.length) {
			System.out.println("Select input file.");
			return;
		}

		try (Scanner in = new Scanner(new File(args[0]))) {
			/*
			 * The 'Set'is a data structure that does not 
			 * contain duplicate entries. We'll use it to filter out 
			 * the duplicate words in the input file.
			 * This way we'll have a much smaller set of 
			 * words to check for isograms.
			*/
			Set<String> set = new HashSet<String>();

			while (in.hasNext()) {
				/*
				 * Some words are 'malformed' - for example they are 
				 * separated from other words with invalid combination
				 * of non-word characters (for example "...", "--", etc).
				 * So we'll split them in separate words. 
				 * Compound words (for instance: "five-pointed", or "It's")
				 * will not be split, because they are considered 
				 * one word (by me)! This can easily be
				 * changed by replacing "{2,}" with "{1,}"
				 */
				String[] splitted = in.next()
						.toLowerCase()
						.split("\\p{Punct}{2,}");
				
				for(String s : splitted){
					/*
					 * The split words may contain invalid characters
					 * (punctuation marks) in the beginning or at the of the word,
					 * so we'll filter them out. This step should be unnecessary if
					 * we have altered the previous RegEx to "\\p{Punct}{1,}"
					 */
					String clean = s.replaceAll("(^+\\p{Punct})|(\\p{Punct}+$)", "");
					/*
					 * After sanitizing the words, there might have left some
					 * strings with length of zero. We'll not add them to the set.
					 */
					if(clean.length() == 0){
						continue;
					}
					
					set.add(clean);
				}
			}

			/*
			 * Export the contents of the set to an array.
			 * We'll sort the array in descending order.
			 * This way we won't need to check every single word
			 * in it if it's an isogram.
			 */
			String[] sa = set.toArray(new String[set.size()]);
			Arrays.sort(sa, new LengthComparator());
			
			/*
			 * We use <code>minLen</code> to store the length
			 * of the longest isogram; 
			 */
			int minLen = 0; 
			/*
			 * Print the longest isograms to screen.
			 * (there may be more than one with the same length)
			 */
			for (String s : sa) {
				/*
				 * If there are no more words with the
				 * length of the longest isogram, we
				 * break the loop
				 */
				if(s.length() < minLen){
					break;
				}
				
				/*
				 * Check if the word stored in <code>s</code> is 
				 * an isogram. If it is, then we store its length
				 * in minLen, and the next loop we'll be checking
				 * only for isograms of the same size.
				 * (These will be the longest isograms, because the 
				 * array is already sorted in desc order)
				 */
				if (isIsogram(s)) {
					minLen = s.length();
					System.out.println(s);
				}
			}
		} catch (Exception e) {
			System.err.println(e);
			e.printStackTrace();
		}
		
		//System.out.println("\nTime:\t" + (System.currentTimeMillis() - start));
	}

}


class LengthComparator implements Comparator<String> {

	@Override
	public int compare(String o1, String o2) {
		if (o1.length() < o2.length()) {
			return 1;
		}

		if (o1.length() > o2.length()) {
			return -1;
		}

		return 0;
	}

}
