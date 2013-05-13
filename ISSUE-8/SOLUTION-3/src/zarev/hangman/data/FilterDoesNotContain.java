package zarev.hangman.data;

import static zarev.util.Utils.*;

public class FilterDoesNotContain implements Filter {
	private String guess;
	
	public FilterDoesNotContain(String guess) {
		checkNotNull(guess);
		this.guess = guess;
	}

	@Override
	public boolean matches(String word) {
		return !word.contains(guess);
	}
}
