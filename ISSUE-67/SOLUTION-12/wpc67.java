public class bookPages {

public static void main(String[] args) {
int check = 9808;
int _int = 0;
float divided = 0;
 for(int i=2; i<check/2 + 1; i++){   // Check all the numbers, There is
also 9808, but................
divided = (float)check / i;
_int = (int) divided;
 if((divided == _int -.5 || divided == _int +.5 )){
int start = -(i/2 -1);
if(start + _int > 0){
System.out.print(start + _int + " + ");
for(int j=start + 1; j < start+i; j++){
System.out.print(" + " + (_int + j));
}
System.out.println(" = " + check);
}
}
}
 }
}
//result 291 +  + 292 + 293 + 294 + 295 + 296 + 297 + 298 + 299 + 300 + 301
+ 302 + 303 + 304 + 305 + 306 + 307 + 308 + 309 + 310 + 311 + 312 + 313 +
314 + 315 + 316 + 317 + 318 + 319 + 320 + 321 + 322 = 9808
