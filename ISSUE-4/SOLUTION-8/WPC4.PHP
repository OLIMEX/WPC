<code><?php

	$infile="http://fiction.eserver.org/novels/alice_in_wonderland.html";
	$outfile="alice.txt";
	$start = "<BLOCKQUOTE>";
	$end = "</BLOCKQUOTE>";

function emsg($msg)
{
	echo "$msg";
	die(1);
}

if(!file_exists($outfile))
{
	$ifp = fopen($infile,"rb");
	if($ifp === false)
	emsg("Cannot read from $infile");
	$ofp = fopen($outfile,"wb");
	if($ofp === false)
	{
		fclose($ifp);
		emsg("Cannot write to $outfile");
	}
	$started = false;
	$ended = false;
	$isogram = "a";
	$isolen = strlen($isogram);
	while(($data = fgets($ifp, 4096)) !== false)
	{
		if(strstr($data,$start) !== false)
		$started = 1;
		if(strstr($data,$end) !== false)
			$ended = 1;
		if($started !== false && $ended === false)
		{
			if($started != 1) // skip first line
			{
				$strippeddata = htmlspecialchars_decode(strip_tags($data));
				if($strippeddata != "")
				{
					fwrite($ofp, $strippeddata);
					$strippeddata = strtolower($strippeddata);
					$strippeddata = preg_replace("/[^a-z \-]/", "", $strippeddata);

					$split = explode(" ", $strippeddata);
					foreach($split as $word)
					{
						$isIsogram = true;
						$len = strlen($word);
						if($isolen < $len)
						{
							for($pos = 0; $pos != $len; $pos++)
							{
								$p = strpos($word, $word[$pos], $pos + 1);
								if($p !== false)
								{
									$isIsogram = false;
									break;
								}
								echo "$word\r\n";
							}
							if($isIsogram)
							{
								$isogram = $word;
								$isolen = $len;
							}
						}
					}
				}
			}
			$started++;
		}
	}
	fclose($ifp);
	fclose($ofp);
	echo "\r\n",$started - 1, " lines processed\r\nLongest isogram: $isogram
	(", strlen($isogram)," characters)\r\n";
}

?></code>
