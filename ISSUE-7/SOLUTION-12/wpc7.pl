% Cat can jump one or two steps on stairs, make code which calculate how 
% many different ways the cat can climb from bottom to top of N-size stairs.
% b-prolog

steps(Limit):-
	findall(X,uniq_perm_count(Limit,X),Solutions), 
	N is sum(Solutions), % sumlist(Solutions,N),
	format("~g solutions.~n",[N]).

combine(Limit,[Head|_],Remainder,[Head]):-
	Limit>=Head,
	Remainder is Limit-Head.
combine(Limit,[Head|Tail],Remainder,[Head|Solution]):-
	Limit>=Head,
	NewLimit is Limit-Head, 
	combine(NewLimit,[Head|Tail],Remainder,Solution).
combine(Limit,[_|Tail],Remainder,Solution):-
	Limit>0,
	combine(Limit,Tail,Remainder,Solution).

factorial(0,1):-!.
factorial(N,X):-
	NN is N-1, 
	factorial(NN,X1), 
	X is X1*N.

uniq_perm_count(Limit,Result):-
	% sum(C)=Limit, Result=N!/(N1!*N2!)
	combine(Limit,[1,2],0,C), length(C,N), factorial(N,NF),
	findall(X,(member(X,C),X=1),AS), length(AS,A), factorial(A,AF),
	findall(X,(member(X,C),X=2),BS), length(BS,B), factorial(B,BF),
	Result is NF/(AF*BF),
	format("P=~d~t ~w~n",[Result,C]).
