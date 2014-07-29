<?php
for($a = ((int)sqrt(1000000));$a>0;$a--){
        $b = 1000000/$a;
        if($b==(int)$b && !strpos($b,"0") && !strpos($a,"0") ){
echo $a.' * '.$b."\n";
        }
}
?>

