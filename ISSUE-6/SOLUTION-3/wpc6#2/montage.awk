BEGIN {
	IGNORECASE=1
	if (ARGC!=3) {
		print "error! argc" > "/dev/stderr"
		exit(1)
	}
}

# MAIN
{
	if (FILENAME ~ /sol$/) {
		if (FNR==1) next
		tour[++i]=$1
	}
	else {
		pos[FNR]=$0
	}
}

END {
	l=length(tour)
	print pos[1]
	for (i=1;i<=l;i++) { # skip dimension and 0 node
		node=tour[i]
	       	if (node!=0) print pos[node+1]
	}
}
