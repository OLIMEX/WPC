<?php
 
  // Olimex Weekend Programming Challenge Issue #20 - Anagrams
  ////////////////////////////////////////////////////////////
  //
  // An anagram is a type of word play, the result of rearranging the letters
  // of a word or phrase to produce a new word or phrase, using all the original
  // letters exactly once; for example orchestra can be rearranged into carthorse. 
  //
  // Problem: Find all anagram words in text file
  //
  // Solution using php maps.
  //
  // Limitations: it needs to be enhanced for the English language. E.g. the word 'hadn't' 
  // is converted by the program to 2 words: 'hadn' and 't', so that if finds 'hand' as
  // an anagram of 'hadn'.
  //
  // Kris Godart - 2013-08-03


function def_anagram($word) {
  $chars = str_split($word);  // Create an array of the characters of the word
  sort($chars);               // Sort the array
  return implode($chars);     // Glue the characters together => default non-sense anagram of the word
}


function find_anagrams(&$input) {
  // Set the inputstring to lower case
  $a_input = strtolower($input); 
  
  // Replace all non-alphabetical characters by a space
  $a_input = preg_replace("/[^\w]+/", " ", $a_input);

  // Split the text in words
  $a_input = explode(' ', $a_input);

  // This is a map: the key is the default anagram, the value is an array
  // of words that have the same default anagram.
  // The default anagram of a word is the characters of the word sorted in
  // alphabetical order
  $anagrams = array();
  
  foreach ($a_input as $word) {
    $def_anagram = def_anagram($word);

    // Add the word to the anagram map if its default anagram does not exist yet as key
    // or if the word does not exist yet as value in the array associated with the 
    // default anagram
    if ((array_key_exists($def_anagram, $anagrams) == false) ||
        (in_array($word, $anagrams[$def_anagram]) == false)) {
      $anagrams[$def_anagram][] = $word;
    }
  }

  return $anagrams;
}


function print_anagrams(&$input) {
  $anagrams = find_anagrams($input);

  $count = 0;
  print("The text contains the following anagrams:\r\n");

  foreach ($anagrams as $anagram) {
    if (count($anagram) > 1) {
      print(implode(", ", $anagram) . "\r\n");
      $count++;
    }
  }

    if ($count == 0) {
      print("  Oops, no anagrams found!\r\n");
    }
}


//////////////////////////////////////////////////////

function main($argv) {
  if (count($argv) != 2) {
    print("Usage: $argv[0] <file>\r\n");
    exit;
  }

  $file = $argv[1];

  if (!file_exists($file)) {
    print ("Error: can not open the file $file.\r\n");
    exit;
  }

  $input = file_get_contents($file);

  if ($input === false) {
    print ("Error: something went wrong during read of file $file.\r\n");
    exit;
  }

  print_anagrams($input);

}

main($argv);

?>