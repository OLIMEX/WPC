<pre>
<?php
// Hey, it's ugly. But it werks!
$time = explode(' ', microtime()); // Boom! We want to know the time for this race!
$start = $time[1] + $time[0];

error_reporting(-1);
$numbers = '123456789';
$result = 100;
$signs = array(' ','+','-');
$right = 0; // How many times we got the 

function getresult($left) {
	$regexp = '/(\-|\+)[0-9]*/'; // Look at this awesomeness! I can't understand it neither!
	$res = 0; // Php gonna issue a notice here
	preg_match_all($regexp, $left, $pieces); // +1+2-34 -> array('+1','+2','-34')
	foreach($pieces[0] as $operation) { // Let's sum everything!
		$res += intval($operation);
	}
	return $res;
}

$combinations = pow(count($signs),strlen($numbers));
echo "Number of combinations: $combinations \n\n";

for($i = 0;$i < $combinations;$i++) { // Iterate between all combinations possible
	$eq_signs = '+'.str_replace(array('0','1','2'), $signs,base_convert($i, 10, 3)); // Look at this! We use a base-3 number to get all the combinations!!!1!
	$left = ''; // Php complains
	for($l = 0; $l < strlen($numbers); $l++) { // Join the strings
		$left .= substr($eq_signs, $l, 1); 
		$left .= substr($numbers, $l, 1);
	}

	$left = str_replace(' ', '', $left); // Remove the spaces
	$eq_result = getresult($left); // Get the result
	if($eq_result == $result) { // Are we winning?
		$right++;
		echo substr($left,1).' = '.$result."\n";
	}
}

echo "\nWe got $right solutions!\n";

$time = explode(' ', microtime());
$time = $time[1] + $time[0];
$total_time = round(($time - $start), 4); // OMG SUCH FASTNESS

echo "Hey, check this out! $total_time seconds for $combinations different equations!";

?>
</pre>
