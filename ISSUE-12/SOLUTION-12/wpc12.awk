#!/usr/bin/gawk -f
#
# make it executable and start it like
#
#	./wpc12.awk -v s="Alice" textfile
#

BEGIN {
	IGNORECASE=1
	RS="[^a-z]" 
	SUBSEP="@"

	if (s=="") s="Alice"
}

# distance between s and t
# http://pl.wikipedia.org/wiki/Odleg%C5%82o%C5%9B%C4%87_Levenshteina

function lev(s,t, ls,lt,i,j,d,cost,del,ins,chg,tmp) {

	split(s,s_a,""); l_s=length(s)
	split(t,t_a,""); l_t=length(t)

	for (i=0;i<=l_s;i++) d[i,0]=i
	for (j=0;j<=l_t;j++) d[0,j]=j

	for (i=1;i<=l_s;i++) {
		for (j=1;j<=l_t;j++) {
			cost=(s_a[i]==t_a[j])? 0: 1

			del=d[i-1,j]+1
			ins=d[i,j-1]+1
			chg=d[i-1,j-1]+cost

			# minimum of del,ins,chg
			tmp=(del<ins)? del: ins
			tmp=(tmp<chg)? tmp: chg

			d[i,j]=tmp
		}
	}
	return d[l_s,l_t]
}

{
	d=lev(s,$0)
	cnt[d]+=1
	distance[d,cnt[d]]=$0
}

END {
	print s
	for (d=1;d<=length(s)-1;d++) 
		if (d in cnt) {
			for(i=1;i<=cnt[d];i++) words[tolower(distance[d,i])]
			for (word in words) printf("[%d] %s\n",d,word)
			exit
		}
	
}

