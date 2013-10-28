% converter from Decimal to Roman numbers

conv(X) :- X >= 1000, write('M'),!,    NX is X-1000, conv(NX).
conv(X) :- X >= 900,  write('CM'),!,   NX is X-900,  conv(NX).
conv(X) :- X >= 500,  write('D'),!,    NX is X-500,  conv(NX).
conv(X) :- X >= 400,  write('CD'),!,   NX is X-400,  conv(NX).
conv(X) :- X >= 100,  write('C'),!,    NX is X-100,  conv(NX).
conv(X) :- X >= 90,   write('XC'),!,   NX is X-90,   conv(NX).
conv(X) :- X >= 50,   write('L'),!,    NX is X-50,   conv(NX).
conv(X) :- X >= 40,   write('XL'),!,   NX is X-40,   conv(NX).
conv(X) :- X >= 10,   write('X'),!,    NX is X-10,   conv(NX).
conv(X) :- X = 9,     write('IX'),!,   NX is X-9,    conv(NX).
conv(X) :- X = 8,     write('VIII'),!, NX is X-8,    conv(NX).
conv(X) :- X = 7,     write('VII'),!,  NX is X-7,    conv(NX).
conv(X) :- X = 6,     write('VI'),!,   NX is X-6,    conv(NX).
conv(X) :- X = 5,     write('V'),!,    NX is X-5,    conv(NX).
conv(X) :- X = 4,     write('IV'),!,   NX is X-4,    conv(NX).
conv(X) :- X = 3,     write('III'),!,  NX is X-3,    conv(NX).
conv(X) :- X = 2,     write('II'),!,   NX is X-2,    conv(NX).
conv(X) :- X = 1,     write('I'),!,    NX is X-1,    conv(NX).
conv(X) :- X = 0,     nl,!.

