This is a C# WinForms application that reads a passage of text from the AlicesAdventuresInWonderland text file and displays it on the form in a scrollable textbox.  The user gets an excerpt of text from the passage (by selecting the number of words and clicking the "Get test text" button), and then tries to type that into the second text box.  As soon as the user starts typing, a stopwatch starts ticking.  The stopwatch is stopped when the Enter key is hit, and the app then displays:

- how long it took to type the excerpt
- the words per minute typing speed
- how accurate the typing was (use of the backspace key lowers your score!)
- and based on this speed, how long it would take to type the whole passage (without any tea breaks!)