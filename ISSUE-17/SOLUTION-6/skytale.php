<?php 
  // Skytale: greek encryption method
  // Wrap a strip around a stick, write the message on it
  // and then unwrap.

  // Target is to get a one liner implementation iso loops
 
  // Kris Godart - 2013-07-14


// Decoder
//////////
// str_split: splits the string into an array
// array_chunk:  converts a 1D array to a 2D array where each row has  $d characters
// array_merge(array(null), array1): prepends the null element in front of the array
// call_user_func_array: calls array_map with null as callback function and a number of arrays (the rows of the 2d matrix) 
// => result is that the 2D array is transposed
// implode(array_map('implode', 2d_array) : will concatenate the caracters first on a column basis and then on row basis to one string
// (consider the 1st index as a row, second index as a column)
function skytale_dec($d, $msg) {
  return implode(array_map('implode', call_user_func_array('array_map', array_merge(array(null), array_chunk(str_split($msg), $d)))));
}


// Encoder
//////////
// Encoder is similar to decoder, so reuse it, only the perimeter is converted to
// the length of the stick or the number of windings that are required.
// Also do some padding of the original message so that its length is an integer
// multiple of the diameter - otherwise there are missing elements in the 2D array
// during conversion. The missing elements get now spaces.
function skytale_enc($d, $msg) {
  return skytale_dec(ceil(strlen($msg)/$d), str_pad($msg, $d*ceil(strlen($msg)/$d)));
}


$msg = "This is the implementation of skytale for the olimex weekend challenge";
$d = 4;  // Number of characters along one winding over the stick
$enc = skytale_enc($d, $msg);
$dec = skytale_dec($d, $enc);
print("Msg: $msg\n");
print("Enc: $enc\n");
print("Dec: $dec\n");
?>