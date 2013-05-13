package zarev.hangman.data;

import static zarev.util.Utils.checkNotNull;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

public class Wordlist implements Filterable, Iterable<String>{
	private static Wordlist instance = null;
	private List<String> words;
	private Random random;

	public static synchronized Wordlist getInstance() {
		if (null == instance) {
			instance = new Wordlist();
		}

		return instance;
	}

	private Wordlist() {
		words = new LinkedList<String>();
		random = new Random();
	}

	public void add(String word) {
		checkNotNull(word);
		words.add(word);
	}
	
	@Override
	public Iterator<String> iterator() {
		return words.iterator();
	}
	
	public int size(){
		return words.size();
	}
	
	public Subset subset(Filter filter){
		checkNotNull(filter);
		Subset subset = new Subset();
		
		for(String s : words){
			if(filter.matches(s)){
				subset.add(s);
			}
		}
		
		return subset;
	}
	
	public String random(){
		if(words.size() == 0){
			return null;
		}
		
		return words.get(random.nextInt(words.size()));
	}

}
