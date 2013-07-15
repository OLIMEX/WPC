#!/usr/bin/php
<?php
$ps = str_split ($argv[2], $d = $argv[1]); for ($c = 0; $c<$d; $c++) foreach ($ps as $p) echo @$p[$c];
?>
