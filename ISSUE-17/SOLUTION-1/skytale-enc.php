#!/usr/bin/php
<?php
$ps = str_split ($argv[2], $d = ceil(strlen($argv[2])/$argv[1])); $ps[count($ps)-1] = str_pad ($ps[count($ps)-1], $d); for ($c = 0; $c<$d; $c++) foreach ($ps as $p) echo @$p[$c];
?>
