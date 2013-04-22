length(4). % =l
distance(4). % =t

go:- genpi(1000,PI), writeln(PI).

genpi(N,PI):-
	gen(N,0,Crosses),
	length(L), distance(T),
	PI is 2*L*N/(Crosses*T).

random(X):- X is random/32769. % b-prolog
randomtheta(Theta):- random(X), Theta is asin(1)*X. % 0 =< Theta =< pi/2

gen(0,Crosses,Crosses):- !.
gen(Step,Acc,Crosses):-
	length(L), distance(T),
	randomtheta(Theta), X is (L/2)*sin(Theta), X=<T/2, X>=0,
	random(Value), (Value*T/2=<X -> Cross is 1 ; Cross is 0),
	NextStep is Step-1, NewAcc is Acc+Cross,
	gen(NextStep,NewAcc,Crosses).
