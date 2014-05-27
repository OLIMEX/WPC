#! /usr/bin/env perl

$url = shift;
$_ = `curl $url`;

$tags = 0;

while(/(<[^>]+>)/g) {
  $tags += length($1);
}

$text = length($_);

$ratio = $text / (1 + $tags);

print "Text $text, and tags $tags; hence $ratio\n";


