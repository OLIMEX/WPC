package zarev.hangman.game.fair;

import zarev.hangman.menu.MenuEntry;

public class PlayFair implements MenuEntry {
	@Override
	public void exec() {
		FairGame fairGame = new FairGame();
		fairGame.play();
	}

	@Override
	public String getName() {
		return "Play fair game";
	}

}
