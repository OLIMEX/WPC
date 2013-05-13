package zarev.hangman.game.unfair;

import java.util.Scanner;

import zarev.hangman.data.FilterDoesNotContain;
import zarev.hangman.data.FilterFactory;
import zarev.hangman.data.FilterNotEquals;
import zarev.hangman.data.LengthFilter;
import zarev.hangman.data.Subset;
import zarev.hangman.data.Wordlist;
import zarev.hangman.game.Game;

public class UnfairGame extends Game{
	
	private Scanner in = new Scanner(System.in);
	private String[] guessed = null;
	private int unknown;
	
	@Override
	public String[] getGuessed() {
		return guessed;
	}
	
	@Override
	public void play() {
		Wordlist words = Wordlist.getInstance();
		if (words.size() == 0) {
			System.out.println("Wordlist is empty. Bye!");
			return;
		}
		
		unknown = words.random().length();
		guessed = new String[unknown];
		
		Subset subset = words.subset(new LengthFilter(unknown));
		
		while((unknown > 0) && (tries() < MAX_TRIES)){
			printGuessed();

			System.out.print("Make a guess: ");
			String guess = in.next();
			
			if (wasTried(guess)) {
				System.out.println("You have already tried that :)");
			} else{
				rememberWord(guess);
				
				if(guess.length() > 1){
					if(guess.length() != guessed.length){
						System.out.println("Hahaha try again :)");
						continue;
					}
					
					Subset filtered = subset.subset(new FilterNotEquals(guess));
					if(filtered.isEmpty()){
						unknown = 0;
					}else{
						subset = filtered;
						wrongGuess();
					}
				}else{
					Subset filtered = subset.subset(new FilterDoesNotContain(guess));
					
					if(filtered.isEmpty()) {
						String word = subset.random();
						unknown -= fillGuessed(word, guess);
						subset = subset.subset(FilterFactory.matchingFilter(guessed));
					} else {
						subset = filtered;
						wrongGuess();
					}
				}
			}
		}
		
		printResult(subset.random());		
		
	}
	
}
