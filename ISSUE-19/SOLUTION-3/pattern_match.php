<?php
 
  // Olimex Weekend Programming Challenge Issue #19 - Pattern match
  /////////////////////////////////////////////////////////////////
  //
  // The function match() takes as input input_string and pattern_string,
  // the input strings may contain any ASCII codes. There are two special
  // codes for use in the pattern-string: ? - replaces 1 character 
  // and * - replaces any character(s)
  //
  // The function prints all words from the input-string which match the pattern-string
  // Words can be separated by any of these characters: " ' , : ;
  //
  // Example:
  // The input-string has this content "The big black cat jump over the window"
  //
  // If pattern-string is "b*"  match() prints: big, black
  // If pattern-string is "*c*" match() prints: black, cat
  // If pattern-string is "?i*" match() prints: big, window
 
  // Open question: Does the the special pattern '?' also matches 0 characters?
  // E.g. "a?c" => "abc" is a valid match, but is "ac" also valid?
  // This implementation does not accept 0 match.
  // Example 2 shows that '*' can also match 0 times

  // This implementation converts the pattern to a regular expression
  // and then uses preg_match(), a built in php function, to do the actual
  // pattern matching.

  // Kris Godart - 2013-07-27


function match($input, $pattern) {
  // Convert the pattern to a regular expression in order to use preg_match(), a built in php function.

  $pattern = trim($pattern);  // Remove whitespace at start and end of the pattern

  // Escape special characters for regular expression in case the user want to search for these
  // Note ? and * are special symbols in regular expressions as well.
  $pattern = preg_quote($pattern);

  // '?' - replaces 1 character - in a regexp this is '.'
  // Due to preg_quote, '?' has been modified to '\?'
  $pattern = str_replace ("\\?", ".", $pattern);    // Replace '\?' by '.'
  
  // '*' - replaces any characters - in a regexp this is '.*'
  // Due to preg_quote, '*' has been modified to '\*'
  $pattern = str_replace ("\\*", ".*", $pattern);   // Replace '\*' by '.*'

  // Add delimiters and make sure that the pattern does not start to match from half the word
  $pattern = str_replace ("/", "\\/", $pattern);   // Escape the used delimiter
  $pattern = "/^$pattern$/";  // Regular expression is ready

  $a_words = explode(" ", $input);  // Split the input string on word basis into an array

  // Now match every word and add it to the result array 
  $a_result = array();

  foreach($a_words as $word) {
    if (preg_match($pattern, $word)) {
      $a_result[] = $word;
    }
  }


  return implode(", ", $a_result); // Concatenate the words and separate them using ', '
}


// Test the examples
$input      = "The big black cat jump over the window";
$a_patterns = array("b*", "*c*", "?i*");

foreach ($a_patterns as $pattern) {
  print("match(\"$input\", \"$pattern\") => " . match($input, "$pattern") . "\n");
}


// Running the script gives this result:
// php>php pattern_match.php
// match("The big black cat jump over the window", "b*") => big, black
// match("The big black cat jump over the window", "*c*") => black, cat
// match("The big black cat jump over the window", "?i*") => big, window


?>