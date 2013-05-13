package zarev.hangman.data;

import static zarev.util.Utils.checkNotNull;

import java.util.regex.Pattern;

public class FilterMatches implements Filter {
	
	private Pattern pattern = null;
	
	public FilterMatches(String regEx) {
		checkNotNull(regEx);
		
		pattern = Pattern.compile(regEx);
	}
	
	
	@Override
	public boolean matches(String word) {
		checkNotNull(word);
		return pattern.matcher(word).matches();
	}

}
