<?php
/**
Usage example:
$ echo "1 2 3 4 5 6 7 8 9 = 100" | php wpc-61.php

Output:
1 + 2 + 3 - 4 + 5 + 6 + 78 + 9 = 100
*/

$input = file_get_contents('php://stdin');

$lr = explode("=", $input);
$numbers = explode(" ", trim($lr[0]));
$result = (int) trim($lr[1]);

$signs = array('-', '+', '|');
$signsCount = count($signs);
$numbersInnerLength = count($numbers) - 1;
$cLength = pow($signsCount, $numbersInnerLength);
$combinations = array();

for ($i = 0; $i < $cLength; $i++) {
    $newArray = array();
    for ($j = 0; $j < $numbersInnerLength + 1; $j++) {
        $newArray[$j * 2] = $numbers[$j];
    }
    $combinations[] = $newArray;    
}


for ($k = 0; $k < $numbersInnerLength; $k++) {
    $periodLength = $cLength / pow($signsCount, $k + 1);
    $signIndex = 0;
    for ($i = 0; $i < $cLength; $i += $periodLength) {
        for ($j = 0; $j < $periodLength && $i + $j < $cLength; $j++) {
            $combinations[$i + $j][$k * 2 + 1] = $signs[$signIndex];
        }
        $signIndex = ($signIndex + 1) % $signsCount;
    }
}
$cLen = count($combinations);

for ($i = 0; $i < $cLen ; $i++) {
    $combination = $combinations[$i];
    $cstr = '';
    for ($k = 0; $k < count($combination); $k++) {
      $cstr .= $combination[$k];
    }
    $cstr = str_replace('|', '', $cstr);

    $ev = eval('$resultEval = (' . $cstr . ');');
    if ($resultEval == $result) {
        $cstr = str_replace('-', ' - ', $cstr);
        $cstr = str_replace('+', ' + ', $cstr);

        echo "$cstr = $result\n";
    	exit(); 
    }
}

