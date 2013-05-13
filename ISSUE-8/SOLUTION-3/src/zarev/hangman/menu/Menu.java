package zarev.hangman.menu;

import static zarev.util.Utils.*;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Menu {

	private List<MenuEntry> entries;
	private MenuEntry onExit;
	private String name;
	private Scanner in;
	private boolean exit;

	public Menu() {
		this("Menu");
	}

	public Menu(String name) {
		this(name, new MenuEntry() {
			@Override
			public String getName() {
				return "Exit";
			}

			@Override
			public void exec() {
				// do nothing;
			}
		});
	}

	public Menu(String name, MenuEntry onExit) {
		checkNotNull(onExit, "MenuEntry 'onExit' is null");
		checkNotNull(name, "Menu name is null");

		this.onExit = onExit;
		this.name = name;

		this.entries = new ArrayList<MenuEntry>();
		in = new Scanner(System.in);
	}

	private void execEntry(MenuEntry entry) {
		checkNotNull(entry);
		try {
			entry.exec();
		} catch (Exception e) {
			System.err.println("Shit happened while executing entry "
					+ entry.getName());
			e.printStackTrace();
		}
	}

	private void display() {
		System.out.println("\n###\t" + name + "\n");

		int i = 1;
		for (i = 1; i <= entries.size(); i++) {
			System.out.format("\n%2d#\t%s", i, entries.get(i - 1).getName());
		}
		System.out.format("\n%2d#\t%s", i, onExit.getName());
	}

	private MenuEntry getChoice() {
		try {
			System.out.print("\n\nEnter your choice: ");
			int choice = in.nextInt();
			if (choice > 0 && choice <= entries.size()) {
				MenuEntry entry = entries.get(choice - 1);
				return entry;
			} else if (choice == entries.size() + 1) {
				exit = true;
				return onExit;
			}

		} catch (Exception e) {
			in.nextLine();
		}	
		
		return null;

	}

	public void show() {
		MenuEntry entry = null;
		while (!exit) {
			display();
			entry = getChoice();
			if (null == entry) {
				System.out.println("Invalid choice!");
				continue;
			}
			execEntry(entry);
		}
	}

	public void add(MenuEntry entry) {
		checkNotNull(entry);
		entries.add(entry);
	}

	public void remove(MenuEntry entry) {
		checkNotNull(entry);
		entries.remove(entry);
	}

	public void remove(int entry) {
		entries.remove(entry);
	}
}
