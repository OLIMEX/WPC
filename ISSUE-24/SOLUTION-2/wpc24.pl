% Display the ways you can express positive natural number
% N as sum of positive natural numbers (b-prolog)

% combine(+N, +AllowedValues, ?Remainder, -Solution)
combine(Limit, [Head|_], Remainder, [Head]):-
	Limit >= Head,
	Remainder is Limit - Head.
combine(Limit, [Head|Tail], Remainder, [Head|Solution]):-
	Limit >= Head,
	NewLimit is Limit-Head,
	combine(NewLimit, [Head|Tail], Remainder, Solution).
combine(Limit, [_|Tail], Remainder, Solution):-
	Limit > 0,
	combine(Limit, Tail, Remainder, Solution).

go(N):-
	Values @= [X: X in 1..N],
	combine(N, Values, 0, Solution), 
	format("~d=",[N]),
	foreach(
		I in 1..Solution^length, 
		[T], 
		(
			T @= Solution[I], 
			(I =:= Solution^length -> format("~d",[T]); format("~d+",[T]))
		)
	), nl,
	fail.
