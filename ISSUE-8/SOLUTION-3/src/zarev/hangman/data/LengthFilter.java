package zarev.hangman.data;

import static zarev.util.Utils.checkNotNull;

public class LengthFilter implements Filter {
	private int minLen, maxLen;

	public LengthFilter(int len) {
		this(len, len);
	}

	public LengthFilter(int minLen, int maxLen) {
		if (minLen <= 0) {
			throw new IllegalArgumentException("MinLen is <= 0 -> minLen == "
					+ minLen);
		}

		if (minLen <= 0) {
			throw new IllegalArgumentException("MaxLen is <= 0 -> maxLen == "
					+ maxLen);
		}

		if (minLen > maxLen) {
			throw new IllegalArgumentException("MinLen is greater than MaxLen!");
		}

		this.minLen = minLen;
		this.maxLen = maxLen;
	}

	@Override
	public boolean matches(String word) {
		checkNotNull(word);
		if (word.length() >= minLen && word.length() <= maxLen) {
			return true;
		}

		return false;
	}

}
