%--------    Quelle: http://de.wikipedia.org/wiki/Stammbruch        ------%
%--------     Egyptian fraction                                     ------%
%--------     unit fraction of a propper fraction                   ------%
%--------  Erich Stöhr; Germany; Schongau; 26.05.2013               ------%

clear all
clc

a =6
b =7
i=1;
if  ( (a/b) < 1 )

 while (1)
     
  c   = a; 
  n   = ceil (b/a);
  N(i)= n;
  i   = i+1;
  d   = n*a;

  if ( mod ( (n*b),(n*a-b) ) == 0 ) 
       n   = (n*b) / (n*a-b) ; 
       N(i)= n;
       break;  % unit fraction -> finished            
  else
       % no unit fraction -> repeat 
       a = (n*a-b);
       b = (n*b);
  end
  
 end 
 
end
 
% Output
N

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  some results 
  
% a = 6
% b = 7
% N = 2     3    42
   
% a = 3
% b = 4
% N = 2   4

% a = 7
% b = 11
% N = 2    8    88

% a =  625
% b =  44536
% N =  72  6911  197863905  9.1350e+16   7.8233e+32








