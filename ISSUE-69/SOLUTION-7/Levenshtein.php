<?php

/**
 * Calculate Levenshtein's distance
 *
 * @param string $string1
 * @param string $string2
 * @return int
 */
function levenshteinDist($string1, $string2)
{
    $string1Length = mb_strlen($string1, mb_detect_encoding($string1));
    $string2Length = mb_strlen($string2, mb_detect_encoding($string2));
    $distance = range(0, $string2Length);

    for ($x = 1; $x <= $string1Length; $x++)
    {
        $distanceNew[0] = $x;
        for ($y = 1; $y <= $string2Length; $y++)
        {
            $diagonal = ($string1[$x - 1] === $string2[$y - 1]) ? 0 : 1;
            $distanceNew[$y] = min(
                $distance[$y] + 1,
                $distanceNew[$y - 1] + 1,
                $distance[$y - 1] + $diagonal
            );
        }
        $distance = $distanceNew;
    }

    return $distance[$string2Length];
}

$result = levenshteinDist('kitten', 'sitting');
echo "Levenstein's distance: ".$result;