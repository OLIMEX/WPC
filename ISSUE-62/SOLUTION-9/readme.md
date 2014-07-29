
Hello people at Olimex,

Thanks again for the nice quiz.

I made the solution in 5 steps. The first 2 steps just by logical thinking; the last 3 steps done by the computer in less than 30 ms, at least on my server. The program can be executed on:

http://www.si-kwadraat.nl/olimex/wp250714.php

Program is written in PHP and the end result is: X = 15625 and Y = 64!!!

The coding:

/********************************************************************************************************************

<?php
function getp($par,$def){
    $val=$def;
    if(isset($_GET[$par]) && $_GET[$par]!=''){
        $val=$_GET[$par];
    };
    return $val;
};
$calc=getp('calc',0); // step 1 $calc=0; text only -- step 2 $calc=1 calculation

echo "<HTML><HEAD><TITLE>X*Y=1000000</TITLE></HEAD><BODY>\n";
echo "<H1>X * Y = 1000000 (Both X and Y do not contain any 0)</H1>\n";
echo "Step 1: One of the numbers should end with a 5 to get the last 0 (let us say X).<BR>\n";
echo "Step 2: Y should be at least 2; this means X<500000.<BR>\n";
echo "Step 3: Y = 1000000 / X; Y should be an integer; skip all X-values which do not result in an integer.<BR>\n";
echo "Step 4: We skip the values of X which contain one or more 0s.<BR>\n";
echo "Step 5: Y should not contain any 0.<HR>\n";
echo "Step 1 leaves 100000 possible values of X<BR>\n";
echo "Step 2 leaves 50000 possible values of X<BR>\n";
if($calc==0)
{
  echo "We will check these 50000 X-values in a loop after pressing the button<BR>\n";
  echo "<FORM method='POST' action='wp250714.php?calc=1'><input type='submit' value='calculate'></FORM><BR>\n";
}
else
{
  // start calculation here
  $starttime=microtime($get_as_float=true);
  for($loop=0;$loop<50000;$loop++)
  {
    $x=(10*$loop)+5; // X value to check
    $y = 1000000 / $x; // calculate companion Y
    if ($y == floor($y)) // is Y an integer
    {
      $s3++; // increment the number of possible values after step 3
      $x_str = (string)$x; // convert to string
      if (strpos($x_str,"0") === false) // No 0s in X
      {
        $s4++; // increment the number of possible values after step 4
        $y_str = (string)$y; // convert to string
        if (strpos($y_str,"0") === false) // No 0s in Y
        {
          $s5++; // increment the number of possible values after step 5
          $x_correct = $x;
          $y_correct = $y;
        };
      };
    };
  };
  echo "Step 3 leaves ".$s3." possible values of X<BR>\n";
  echo "Step 4 leaves ".$s4." possible values of X<BR>\n";
  echo "Step 5 leaves ".$s5." possible values of X<HR>\n";
  echo "<H2> ... and the values are: X = ".$x_correct." and Y = ".$y_correct."!!!</H2><HR>\n";
  echo "Calculated in: ".number_format((microtime($get_as_float=true)-$starttime),3,".","")." seconds.<BR>\n";
};
echo "</BODY></HTML>\n";
?>

****************************************************************************************************************/

Kees Zagers


