#include <iostream>
#include <math.h>
const long maxNum = 9; // the number of digits
const long targetVal = 100; // the number of digits
enum operation {op_append, op_minus, op_plus};

const char* opToStr(operation op)
{
	switch(op) {
		case op_minus:
			return "-";
			break;
		case op_plus:
			return "+";
			break;
		default:
			return "";
			break;
	}
}

int main(int argc, const char * argv[]) {
	long end = pow(3, maxNum - 1); // number of permutations of the three operators "concat", "-", "+"
	char line[256] = "";
	char dbgLine[256*2] = "";
	long pos = 0;
	long dbgPos = 0;
	
	for(long i = 0; i < end ; i++) {
		operation stackOp = op_plus; // initial operation is plus
		long val = 0;
		long ops = i;
		long accu = 0;
		for(long n = 1; n <= maxNum; n++) {
			operation op = static_cast<operation>(ops % 3);
			ops = ops / 3;
			accu = accu * 10 + n;
			if(op != op_append) {
				if(stackOp == op_minus) {
					val -= accu;
				}
				else if(stackOp == op_plus) {
					val += accu;
				}
				accu = 0;
				stackOp = op;
			}
				
			pos += sprintf(&line[0] + pos, "%ld%s", n, opToStr(op));
			dbgPos += sprintf(&dbgLine[0] + dbgPos, "%ld%s(stackOp=%s/val=%ld/accu=%ld) ", n, opToStr(op), opToStr(stackOp), val, accu);
		}
		
		// handle any operations left on the stack
		if(stackOp == op_minus) {
			val -= accu;
		} else {
			val += accu;
		}

		if(val == targetVal) {
			printf("%s = %ld, %s\n", line, val, (val == targetVal) ? "FOUND SOLUTION" : "");
			//printf("  dbg: %s = %ld, %s\n", dbgLine, val, (val == targetVal) ? "FOUND SOLUTION" : "");
		}
		pos = 0;
		dbgPos = 0;
	}
	
    return 0;
}




