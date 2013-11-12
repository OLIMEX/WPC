go((GW,GH)):-
	Bs=[(60,40),(60,40),(60,40),(40,40),(40,40),(20,20),(20,20),(20,20),(20,20)],
	% powierzchnia plytek nie przekracza powierzchni panelu
	Ps @= [X*Y: (X,Y) in Bs],
	sum(Ps) =< GW*GH,

	length(Bs,NB),
	length(S,NB),
	S in 0..GW,
	D @= [X: (X,_) in Bs],
	R @= [Y: (_,Y) in Bs],
	
	cumulative(S,D,R,GH),
	
	% obliczone pozycje plytek nie moga wychodzic poza dostepny obszar
	% funkcja kosztu to ~ powierzchnia ulozenia do sumy powierzchni plytek
	% ich roznica powinna byc maksymalizowana
	
	X @= [S[N]+D[N]: N in 1..NB],
	max(X) #< GW,
	Width #= max(X),

	labeling([min(Width)],S),
	foreach(N in 1..NB, [B,SX,DX,EX,DY],
		(
			B @= Bs[N], % plytka N
			SX @= S[N], % pozycja X od SX do EX
			DX @= D[N], EX is SX+DX,
			DY @= R[N], % wysokosc
			
			format("board ~w x:<~w,~w> y:+~w\n",[B,SX,EX,DY])			
		)).

