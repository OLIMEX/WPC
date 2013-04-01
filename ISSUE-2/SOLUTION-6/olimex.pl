go:-shu([10,2,7,4]).

shu(Input):-
	N is Input^length,
    N > 2,
	new_array(Tmp,[N]),
    Vars @= [Tmp[I] : I in 1..N],
    Vars :: Input,
	% sum(Vars) #= S,
	foreach(
		I in 1..N, 
		J in I+1..N, 
		K in J+1..N, 
		Tmp[I] - Tmp[J] #< Tmp[J] - Tmp[K]
	),
	labeling(Vars),
	Z @= [Tmp[I] : I in 1..N],
	sort(=<,Z,X),
	sort(=<,Input,Y),
	X=Y,
	foreach(
		I in 1..N, 
		[B], (B @= Tmp[I], format("~2d ",[B]))
	), nl,
	fail.
	