package zarev.hangman;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

import zarev.hangman.data.Wordlist;
import zarev.hangman.game.fair.PlayFair;
import zarev.hangman.game.unfair.PlayUnfair;
import zarev.hangman.menu.Menu;


public class Hangman {

	public static void main(String[] args) {
		File wordlist = new File("wordlist.txt");
		
		try(Scanner in = new Scanner(wordlist)){
			Wordlist words = Wordlist.getInstance();

			while(in.hasNextLine()){
				String word = in.nextLine().trim().toLowerCase();
				if(word.matches("\\p{L}+")){
					words.add(word);
				}
			}
		} catch (FileNotFoundException e) {
			System.out.println("Cannot find the wordlist!");
			System.exit(0);
		}
		
		
		Menu menu = new Menu("Hangman");
		
		PlayFair playFair = new PlayFair();
		menu.add(playFair);
		
		PlayUnfair playUnfair = new PlayUnfair();
		menu.add(playUnfair);
		
		menu.show();
	}

}
