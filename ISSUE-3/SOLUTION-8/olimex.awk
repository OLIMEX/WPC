#!/usr/bin/gawk -f

function trim(str) {
	gsub(/^[\t\r ]+/,"",str)
	gsub(/[\t\r ]+$/,"",str)
	return str
}

function to_a(num) {
	return sprintf("%04s",num)
}

BEGIN {
	IGNORECASE=1
	SUBSEP="@"
}

{
	line[NR]=trim($1)
	text=tolower(line[NR])

	for (i=1;i<=length(text);i++) {
		for (j=1;j<=length(text)-i+1;j++) {
			seq=substr(text,i,j)
			freq[seq,to_a(length(seq))]+=1
		}
	}
}

END {
	fn=asorti(freq,fs)
	for (NR=1;NR<=length(line);NR++) {

		text=line[NR]
		split("",order)

		for (i=1;i<=fn;i++) {

			idx=fs[i] # seq@length
			cnt=freq[idx]
			if (cnt!=1) continue

			split(idx,t,SUBSEP)
			seq=t[1]
			size=t[2]

			pos=index(line[NR],seq)
			if (pos>0) order[to_a(cnt),to_a(size),to_a(pos)]=seq
		}

		no=asorti(order,os) 
		seq=(no==0)? "none": order[os[1]]
		print text,"->",seq
	}
}
