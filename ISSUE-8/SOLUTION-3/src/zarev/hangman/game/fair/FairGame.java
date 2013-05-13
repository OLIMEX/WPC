package zarev.hangman.game.fair;

import java.util.Scanner;

import zarev.hangman.data.Wordlist;
import zarev.hangman.game.Game;

public class FairGame extends Game{

	private Scanner in = new Scanner(System.in);	
	private String[] guessed = null;
	

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

		String word = words.random();
		int unknown = word.length();

		guessed = new String[word.length()];

		while ((tries() < MAX_TRIES) && (unknown > 0)) {
			printGuessed();
			System.out.print("Make a guess: ");
			String guess = in.next();
			
			
			if (wasTried(guess)) {
				/*
				 * Does not allow duplicate tries
				 */
				System.out.println("You have already tied that :)");
			} else{
				rememberWord(guess);				
				/*
				 * User has entered a word.
				 */
				if (guess.length() != 1) {
					if(guess.length() != guessed.length){
						System.out.println("Hahaha try again :)");
						continue;
					}
					
					if (guess.equals(word)) {
						unknown = 0;
					} else {
						wrongGuess();
					}
				} else {
					/*
					 * User has entered a letter
					 */
					if(!word.contains(guess)) {
						wrongGuess();
					} else {
						unknown -= fillGuessed(word, guess);
					}
				}
			}
		}
		
		printResult(word);

	}

	
}
