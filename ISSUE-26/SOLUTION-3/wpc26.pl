% check if four points make square
% (0,0),(0,1),(1,1),(1,0) - normal square
% (0,0),(3,4),(8,4),(5,0) - rhombus

square(A,B,C,D) :-
	% distances between points are equal
	distance(A,B,AB),
	distance(B,C,BC),
	distance(C,D,CD),
	distance(D,A,DA),
	AB = BC,
	BC = CD,
	CD = DA,
	DA = AB,
	% diagonal distances are equal
	distance(A,C,AC),
	distance(B,D,BD),
	AC = BD.

distance(A,B,Distance) :-
	(XA,YA) = A,
	(XB,YB) = B,
	Distance is sqrt(((XB - XA) ** 2) + ((YB - YA) ** 2)).
