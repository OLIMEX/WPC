%x1 < x2, CW
A12_CW  = [0,3]; B12_CW  = [2,2]; C12_CW  = [1,1];
%x1 < x2, CCW
A12_CCW = [0,3]; B12_CCW = [1,1]; C12_CCW = [2,2];

%x1 > x2, CW
A21_CW = [1,1];  B21_CW = [0,3]; C21_CW = [2,2];
%x1 > x2, CCW
A21_CCW = [2,2]; B21_CCW  = [0,3]; C21_CCW  = [1,1];

%oneLine
A_oL  = [0,3]; B_oL  = [1,1]; C_oL  = [2,-1];

%special case 1 -> x1 = x2, y1 > y2
%CW
A_S1_CW  = [0,3]; B_S1_CW  = [0,1]; C_S1_CW  = [-2,-1];
%CCW
A_S1_CCW = [0,3]; B_S1_CCW = [0,1]; C_S1_CCW = [2,2];

%special case 2 -> x1 = x2, y1 < y2
%CW
A_S2_CW  = [0,1]; B_S2_CW  = [0,3]; C_S2_CW  = [2,-1];
%CCW
A_S2_CCW = [0,1]; B_S2_CCW = [0,3]; C_S2_CCW = [-2,2];
%oneLine
A_S_oL  = [0,1]; B_S_oL  = [0,3]; C_S_oL  = [0,-1];

%function to calculate the drawing order, expects three points, the conditions for the test as string, expected result as string
function checkCreationOrder(A, B, C, conditions, exp_result)
  printf("Points: A[%i,%i]\n        B[%i,%i]\n        C[%i,%i]\n", A(1), A(2), B(1), B(2), C(1), C(2));
  printf("Special conditions: %s\n", conditions);
  printf("Expected result   : %s\n", exp_result);
  printf("Computed result   : ");

  %special cases
  if(A(1) == B(1))
    if(C(1) > A(1))
      %C right of A and B
      if(A(2) > B(2))
        %special case 1
        printf("CCW");
      else
        %special case 2
        printf("CW");
      endif
    else
      if(C(1) < A(1))
        %C left of A and B
        if(A(2) > B(2))
          %special case 1
          printf("CW");
        else
          %special case 2
          printf("CCW");
        endif
      else
        printf("on one line");
      endif
    endif
  else
    %normal case, build line from A to B with two-point form
    yC = ((B(2) - A(2))/(B(1) - A(1))) * (C(1) - (A(1))) + A(2);
	
    %check if calculated yC is...
    if(yC > C(2))
      %...bigger than real yC (C is BELOW the calculated line)
	  if(A(1) < B(1))
        printf("CW");
	  else
	    printf("CCW");
	  endif
    else
      if(yC < C(2))
        %...smaller than real yC (C is ABOVE the calculated line)
		if(A(1) > B(1))
          printf("CW");
	    else
          printf("CCW");
	    endif
      else
        %... == yC (C is ON the calculated line)
        printf("on one line");
      endif
    endif
  endif

  printf("\n---------------------------\n\n");
endfunction

%test it all
checkCreationOrder(A12_CW,  B12_CW,  C12_CW,   "x1 < x2",          "CW")
checkCreationOrder(A12_CCW, B12_CCW, C12_CCW,  "x1 < x2",          "CCW")
checkCreationOrder(A21_CW,  B21_CW,  C21_CW,   "x1 > x2",          "CW")
checkCreationOrder(A21_CCW, B21_CCW, C21_CCW,  "x1 > x2",          "CCW")
checkCreationOrder(A_oL,    B_oL,    C_oL,     "none",             "on one line")
checkCreationOrder(A_S1_CW, B_S1_CW, C_S1_CW,  "xA = xB, yA > yB", "CW")
checkCreationOrder(A_S1_CCW,B_S1_CCW,C_S1_CCW, "xA = xB, yA > yB", "CCW")
checkCreationOrder(A_S2_CW, B_S2_CW, C_S2_CW,  "xA = xB, yA < yB", "CW")
checkCreationOrder(A_S2_CCW,B_S2_CCW,C_S2_CCW, "xA = xB, yA < yB", "CCW")
checkCreationOrder(A_S_oL,  B_S_oL,  C_S_oL,   "xA = xB, yA < yB", "on one line")
