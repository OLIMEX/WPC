package zarev.hangman.game;

import static zarev.util.Utils.checkNotNull;

import java.util.HashSet;

public abstract class Game {
	public static final int MAX_TRIES = 10;
	
	private int tries;
	private HashSet<String> tried = new HashSet<String>();

	protected boolean wasTried(String word){
		return tried.contains(word);
	}
	
	protected void rememberWord(String word){
		tried.add(word);
	}
	
	protected void wrongGuess(){
		tries++;
	}
	
	public int tries(){
		return tries;
	}
	
	public void printGuessed() {
		System.out.print("\nTries : " + tries() + " of " + MAX_TRIES + "\nGuessed so far: ");
		for (String ch : getGuessed()) {
			if (null == ch) {
				System.out.print(" _ ");
			} else {
				System.out.print(" " + ch + " ");
			}
		}
		System.out.println();
	}
	
	protected void printResult(String answer){
		checkNotNull(answer);
		if(tries() < MAX_TRIES){
			System.out.println("\nGreat! You win :)");
		}else{
			System.out.println("\nYou loose :)");
		}
		System.out.println("The word is: " + answer);
	}
	
	protected int fillGuessed(String word, String guess){
		checkNotNull(word);
		checkNotNull(guess);
		
		assert(guess.length() == 1);
		
		String[] guessed = getGuessed();
		int filled = 0;
		
		int index = 0;
		while(true){
			index = word.indexOf(guess, index);
			if(index >=0 && index < word.length()){
				guessed[index] = guess;
				filled ++;
				index++;
			}else{
				break;
			}
		}
		
		return filled;
	}
	
	
	public abstract void play();
	public abstract String[] getGuessed();
	
	

}
