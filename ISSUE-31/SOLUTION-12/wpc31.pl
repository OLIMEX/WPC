% wpc31 run length encoder/decoder
% ?- [wpc31].
% consulting::wpc31.pl
%
% ?- rle("ooollimeexxx").
% 3o2lim2e3x
% yes
% ?- rld("3o2lim2e3x").
% ooollimeexxx
% yes
  
rle(In) :- pack(In, Rs), stringify(Rs, Zs), flatten(Zs, Ls), atom_codes(Cs,Ls), write(Cs).
  
  % pack(Xs, Rs) zwraca liste [N,X] krotnosci elementow Xs
  pack([], []).
  pack([X|Xs], [R|Rs]) :- shorten(X,Xs, R,Zs), pack(Zs,Rs).
  
  % shorten(X,Xs, [N,X],Zs) zwraca liste Zs po pominieciu N znakow X z listy Xs
  shorten(X,[], [1,X],[]).
  shorten(X,[Y|Ys], [1,X],[Y|Ys]) :- X \= Y. % koniec sekwencji
  shorten(X,[X|Xs], [N,X],Zs) :- shorten(X,Xs, [NN,X],Zs), N is NN+1.

  stringify([], []).
  stringify([[1,Y]|Z], [Y|R]) :- stringify(Z, R). % nie wstawiaj liczby dla krotnosci N=1
  stringify([[X,Y]|Z], [A|R]) :- number_codes(X,N), append(N,[Y],A), stringify(Z, R).
  
rld(In) :- chunks(In, Zs), unpack(Zs, Rs), flatten(Rs, Ls), atom_codes(Cs, Ls), write(Cs).
  
  % num(Xs,Acc, [N,X],Zs) zwraca krotnosc N elementu X oraz liste Xs po ich pominieciu
  % czyli z "12W" robi [12,W]; N moze byc wielocyfrowe
  num([X|Xs],0, [1,X],Xs) :- (X<48; X>57). % gdy brak danych przyjmij krotnosc N=1
  num([X|Xs],N, [N,X],Xs) :- (X<48; X>57).
  num([X|Xs],N, R,Zs) :- X>=48, X=<57, NN is N*10 + X-48, num(Xs,NN, R, Zs).

  % chunks(Xs, Zs) tworzy liste Zs krotnosc elementow listy/tekstu Xs
  chunks([], []).
  chunks(Xs, [N|Zs]) :- num(Xs,0, N,Rs), chunks(Rs, Zs).

  % fill(N,X, Xs) tworzy liste Xs zawierajaca N elementow X
  fill(0,_, []).
  fill(N,X, [X|Xs]) :- N>0, NN is N-1, fill(NN,X,Xs).

  % unpack(Xs, Zs) tworzy liste Zs rozwinieta z zapisu [[N,X]..] do [[X1,..,Xn]..]
  unpack([], []).
  unpack([[N,X]|Zs], [R|Rs]) :- fill(N,X,R), unpack(Zs, Rs).
