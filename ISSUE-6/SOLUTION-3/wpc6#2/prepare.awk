BEGIN {
	IGNORECASE=1
	SUBSEP=","
	drill=0
	maxx=999999
	minx=0
	maxy=999999
	miny=0
}

function trim(s) {
	gsub(/^[\t\r ]+/,"",s)
	gsub(/[\t\r ]+$/,"",s)
	gsub(/[ ]+/,"",s)
	return s
}

function die(s) {
	printf "error! %s\n",s > "/dev/stderr"
	die_and_exit=1
	exit(1)
}

#MAIN
{
	if (FNR==1) {
		if (match($0,/T([0-9][0-9])/,m)) drill=m[1]*100
		if (drill==0) die("no drill")
	}

	if (match($0,/X([0-9]+),?Y([0-9]+)/,m))  {
		x=m[1]
		y=m[2]

		if ((x SUBSEP y) in xy) {
			printf("lines %d and %d are the same",FNR,xy[(x SUBSEP y)])
			next
		}

		if ((x+drill/2)>maxx||(x-drill/2)<minx||(y+drill/2)>maxy||(y-drill/2)<miny)  {
			printf("line %d, point outside\n",FNR)
			next
		}

		xy[x,y]=FNR
	}
}

END {
	if (die_and_exit) exit(1) 
	for (pointa in xy) {

		split(pointa,m,SUBSEP)
		xa=m[1]; ya=m[2]

		for (pointb in xy) {
			if (xy[pointa]==xy[pointb]) continue
			if ((pointa SUBSEP pointb) in seen) continue
			if ((pointb SUBSEP pointa) in seen) continue

			seen[pointa,pointb]
			seen[pointb,pointa]

			split(pointb,m,SUBSEP)
			xb=m[1]; yb=m[2]

			# euclidean distance
			dx=xb-xa
			dy=yb-ya
			d=sqrt(dx*dx+dy*dy)

			if (d<drill) err[++j]=sprintf("lines %d and %d, points too close",
			    	xy[pointa],
				xy[pointb])
		}
	}

	n=length(err)
	if (n>0) {
		for(i=1;i<=n;i++) print err[i] > "/dev/stderr"
		die("no good")
	}
	
	print "NAME : olimex"
	print "COMMENT : wpc6" 
	print "TYPE : TSP"
	print "DIMENSION : " length(xy)
	print "EDGE_WEIGHT_TYPE : EUC_2D"
	print "NODE_COORD_SECTION"
	n=asorti(xy,node)
	for (i=1;i<=n;i++) {
		split(node[i],m,SUBSEP)
		printf "%3d %3.3f %3.3f\n",i,m[1]/1000,m[2]/1000
	}
	print "EOF"
}

