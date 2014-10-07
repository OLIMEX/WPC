/*
Written by Rodrigo Urbina, rope.50@gmail.com

I used the formulation SUM(1,N) = (N+1)/2,
and, SUM(K,N) = SUM(1,N) - SUM(1,K)
with a little of maths we get the expression:

SUM(K,N) =  ((N-K)*(N+K+1))/2

If we graphic the expresion (N-K)(N+K+1)/2 = 9808 
we get a hyperbola, where the min value for 
K is Sqrt(2*9808), and of course,  K never can be 
greater than N. For this reason we start the 
loop with the value Sqrt(9808).

Notice that one possible solution is the page 
9808 alone, but I'm considering that every sheet 
have two pages, so this solution it's not possible.

Best Regards From Chile,
Rodrigo.
*/

function sumPageNumbers(k,n){
	return (n-k)*(n+k+1)/2;
}

var maxPageNumber = 9808,
	valueSqrt = Math.floor(Math.sqrt(2*maxPageNumber)),
	sum;

for(var b = valueSqrt; b <= maxPageNumber ; b++){
	for( var a = b; a > valueSqrt ; a--){
		sum = sumPageNumbers(a,b);
		
		if(sum > maxPageNumber) //break if the summation is out of our range
			break;
		console.log(a, b, sumPageNumbers(a,b));
		
		if(sum === maxPageNumber){
			console.log('The missing pages are between ' + a + ' and '+ b);
			return; //we not want to use the CPU more time than necessary
		}
	}
}

