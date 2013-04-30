#!/bin/bash

points=$1
points=${points:?no file!}
tsp=wpc6

gawk -f prepare.awk $points > $tsp.tsp && \
	(./concorde -xfV $tsp.tsp >&2 || gawk -f montage.awk $points $tsp.sol)

