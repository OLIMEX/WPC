package zarev.hangman.game.unfair;

import zarev.hangman.menu.MenuEntry;

public class PlayUnfair implements MenuEntry {

	@Override
	public void exec() {
		UnfairGame unfairGame = new UnfairGame();
		unfairGame.play();
	}

	@Override
	public String getName() {
		return "Play unfair game";
	}

}
