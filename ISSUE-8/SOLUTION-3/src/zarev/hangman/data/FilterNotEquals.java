package zarev.hangman.data;
import static zarev.util.Utils.checkNotNull;

public class FilterNotEquals implements Filter {
	private final String guess;

	public FilterNotEquals(String guess) {
		checkNotNull(guess);
		this.guess = guess;
	}

	@Override
	public boolean matches(String word) {
		return !word.equals(guess);
	}

}
