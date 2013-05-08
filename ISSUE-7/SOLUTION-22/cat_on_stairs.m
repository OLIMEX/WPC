%--------  cat on stairs   --> can jump one or two steps at once    ------%
%--------    on how many different ways                             ------%
%--------    can the cat climb to the top of N-sized stairs         ------%
%--------  Erich Stöhr; Germany; Schongau; 05.05.2013               ------%

clear all
clc

% Z(N) = ...
% N = stairs;
% Z = different ways to climb on the stairs;  

%  Z(1)=1                 % for one stair  -> one way
%  Z(2)=Z(1)+1   =1+1=2   % for two stairs -> two ways; (**)
%  Z(3)=Z(2)+Z(1)=2+1=3
%  Z(4)=Z(3)+Z(2)=3+2=5   
%  Z(5)=Z(4)+Z(3)=5+3=8   % for 5 stairs -> 8 ways
%  ...
%  Z(k)=Z(k-1)+Z(k-2)     % (***)

% (**) ( Z(1)+1 ) = Z(2) different ways two stairs
% (**) one stair and then the remaining one stair --> Z(1) 
% (**) or two stairs at once                      --> 1 

% (***) Z(k-1)+Z(k-2) = Z(k) different ways for k stairs
% (***) one stair and then the remaining k-1 stairs     --> Z(k-1) 
% (***) or two stairs and then the remaining k-2 stairs --> Z(k-2) 


%  --> Fibonacci sequence

N = 1000 
f(1) = 1;
f(2) = 2; 
for k = 3:1:N 
    f(k) = f(k-1) + f(k-2);
end 
Z = f(N)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  some results 
%  N = 1;   Z =  1
%  N = 2;   Z =  2
%  N = 3;   Z =  3
%  N = 4;   Z =  5
%  N = 5;   Z =  8
%  N = 6;   Z =  13
%  N = 7;   Z =  21
%  N = 8;   Z =  34
% ...
%  N = 30;  Z =  1346269
%  N = 300; Z =  3.5958e+62
%  N = 1000;Z =  7.0330e+208





