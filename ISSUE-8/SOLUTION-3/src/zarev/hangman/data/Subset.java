package zarev.hangman.data;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Random;

import static zarev.util.Utils.checkNotNull;

public class Subset implements Filterable, Iterable<String> {
	private List<String> words = new ArrayList<String>();

	public void add(String word) {
		checkNotNull(word);
		words.add(word);
	}

	@Override
	public Subset subset(Filter filter) {
		checkNotNull(filter);
		Subset subset = new Subset();

		for (String s : words) {
			if (filter.matches(s)) {
				subset.add(s);
			}
		}

		return subset;
	}

	@Override
	public Iterator<String> iterator() {
		return words.iterator();
	}

	public int size() {
		return words.size();
	}

	public boolean isEmpty() {
		return words.isEmpty();
	}

	public String random() {
		int max = words.size();
		if (max > 0) {
			Random random = new Random();
			return words.get(random.nextInt(max));
		}
		return null;
	}

}
