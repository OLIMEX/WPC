%--------  Buffons Needle  -->          estimating Pi               ------%
%--------   with the usage of the short needle crossing probability ------%
%--------  Erich Stöhr; Germany; Schongau; 21.04.2013               ------%
%--------  Quelle 1:                                                ------%
%----- http://en.wikipedia.org/wiki/Buffon's_needle -> estimating Pi -----%
clear all
clc

% l < t; case for short needles
%%% Input
l = 2       % needle length; l < t
t = 7       % stripes width 
n = 100000  % number of needles 
%-----------------------------------------------------
% P = probability that a short needle will cross a line  
% pi = (2*l)/(t*P)          % Quelle 1

% experimental P:
% dropping n needles and find h needles, which are crossing the lines 
% experimental P = h/n;     % Quelle 1

h=0;
for i=1:1:n
    % x =  distance from the center of the needle to the closest line
    x = (t/2)*rand(1);           % random dropping x     from 0 to t/2 
    % theta =  angle of the needle related to the line
    theta = (pi/2)*rand(1);     % random dropping theta from 0 to pi/2 
    if( x <= (l/2)*sin(theta) ) % Quelle 1
        h=h+1;                  % needle cross a line
    end
end
P_experiment  = h/n  
pi_experiment = (2*l)/(t*P_experiment) 
pi_error      = abs(pi_experiment - pi)

% Test: P calculated  ->
% is very close to  P_experiment (if n is large) -> OK
P_calc_test   = (2*l)/(t*pi) 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  some results (rounded)
%  l=2; t=7; n=100; P_experiment=0.1400; pi_experiment=4.0816
%  pi_error=0.9400; P_calc_test=0.1819
%
%  l=2; t=7; n=100000; P_experiment=0.1816; pi_experiment=3.1473
%  pi_error=0.0057; P_calc_test=0.1819
%
%  l=2; t=7; n=10000000; P_experiment=0.1819; pi_experiment=3.1406
%  pi_error=9.7618e-04; P_calc_test=0.1819








