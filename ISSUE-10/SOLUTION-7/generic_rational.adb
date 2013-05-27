package body Generic_Rational is
 
   function GCD (A, B : Number) return Number is
   begin
      if A = 0 then
         return B;
      end if;
      if B = 0 then
         return A;
      end if;
      if A > B then
         return GCD (B, A mod B);
      else
         return GCD (A, B mod A);
      end if;
   end GCD;
 
   function Inverse (A : Rational) return Rational is
   begin
      if A.Numerator > 0 then
         return (A.Denominator, A.Numerator);
      elsif A.Numerator < 0 then
         return (-A.Denominator, -A.Numerator);
      else
         raise Constraint_Error;
      end if;
   end Inverse;
 
   function "abs" (A : Rational) return Rational is
   begin
      return (abs A.Numerator, A.Denominator);
   end "abs";
 
   function "+" (A : Rational) return Rational is
   begin
      return A;
   end "+";
 
   function "-" (A : Rational) return Rational is
   begin
      return (-A.Numerator, A.Denominator);
   end "-";
 
   function "+" (A : Rational; B : Rational) return Rational is
      Common        : constant Number := GCD (A.Denominator, B.Denominator);
      A_Denominator : constant Number := A.Denominator / Common; 
      B_Denominator : constant Number := B.Denominator / Common; 
   begin
      return (A.Numerator * B_Denominator + B.Numerator * A_Denominator) /
             (A_Denominator * B.Denominator);
   end "+";
 
   function "+" (A : Rational; B : Number) return Rational is
   begin
      return (A.Numerator + B * A.Denominator) / A.Denominator;
   end "+";
 
   function "+" (A : Number; B : Rational) return Rational is
   begin
      return B + A;
   end "+";
 
   function "-" (A : Rational; B : Rational) return Rational is
   begin
      return A + (-B);
   end "-";
 
   function "-" (A : Rational; B : Number) return Rational is
   begin
      return A + (-B);
   end "-";
 
   function "-" (A : Number; B : Rational) return Rational is
   begin
      return A + (-B);
   end "-";
 
   function "*" (A : Rational; B : Rational) return Rational is
   begin
      return (A.Numerator * B.Numerator) / (A.Denominator * B.Denominator);
   end "*";
 
   function "*" (A : Rational; B : Number) return Rational is
      Common : constant Number := GCD (A.Denominator, abs B);
   begin
      return (A.Numerator * B / Common, A.Denominator / Common);
   end "*";
 
   function "*" (A : Number; B : Rational) return Rational is
   begin
      return B * A;
   end "*";
 
   function "/" (A : Rational; B : Rational) return Rational is
   begin
      return A * Inverse (B);
   end "/";
 
   function "/" (A : Rational; B : Number) return Rational is
      Common : constant Number := GCD (abs A.Numerator, abs B);
   begin
      if B > 0 then
         return (A.Numerator / Common, A.Denominator * (B / Common));
      else
         return ((-A.Numerator) / Common, A.Denominator * ((-B) / Common));
      end if;
   end "/";
 
   function "/" (A : Number; B : Rational) return Rational is
   begin
      return Inverse (B) * A;
   end "/";
 
   function "/" (A : Number; B : Number) return Rational is
      Common : constant Number := GCD (abs A, abs B);
   begin
      if B = 0 then
         raise Constraint_Error;
      elsif A = 0 then
         return (0, 1);
      elsif A > 0 xor B > 0 then
         return (-(abs A / Common), abs B / Common);
      else
         return (abs A / Common, abs B / Common);
      end if;
   end "/";
 
   function ">" (A, B : Rational) return Boolean is
      Diff : constant Rational := A - B;
   begin
      return Diff.Numerator > 0;
   end ">";
 
   function ">" (A : Number; B : Rational) return Boolean is
      Diff : constant Rational := A - B;
   begin
      return Diff.Numerator > 0;
   end ">";
 
   function ">" (A : Rational; B : Number) return Boolean is
      Diff : constant Rational := A - B;
   begin
      return Diff.Numerator > 0;
   end ">";
 
   function "<" (A, B : Rational) return Boolean is
      Diff : constant Rational := A - B;
   begin
      return Diff.Numerator < 0;
   end "<";
 
   function "<" (A : Number; B : Rational) return Boolean is
      Diff : constant Rational := A - B;
   begin
      return Diff.Numerator < 0;
   end "<";
 
   function "<" (A : Rational; B : Number) return Boolean is
      Diff : constant Rational := A - B;
   begin
      return Diff.Numerator < 0;
   end "<";
 
   function ">=" (A, B : Rational) return Boolean is
      Diff : constant Rational := A - B;
   begin
      return Diff.Numerator >= 0;
   end ">=";
 
   function ">=" (A : Number; B : Rational) return Boolean is
      Diff : constant Rational := A - B;
   begin
      return Diff.Numerator >= 0;
   end ">=";
 
   function ">=" (A : Rational; B : Number) return Boolean is
      Diff : constant Rational := A - B;
   begin
      return Diff.Numerator >= 0;
   end ">=";
 
   function "<=" (A, B : Rational) return Boolean is
      Diff : constant Rational := A - B;
   begin
      return Diff.Numerator <= 0;
   end "<=";
 
   function "<=" (A : Number; B : Rational) return Boolean is
      Diff : constant Rational := A - B;
   begin
      return Diff.Numerator <= 0;
   end "<=";
 
   function "<=" (A : Rational; B : Number) return Boolean is
      Diff : constant Rational := A - B;
   begin
      return Diff.Numerator <= 0;
   end "<=";
 
   function "=" (A : Number; B : Rational) return Boolean is
      Diff : constant Rational := A - B;
   begin
      return Diff.Numerator = 0;
   end "=";
 
   function "=" (A : Rational; B : Number) return Boolean is
      Diff : constant Rational := A - B;
   begin
      return Diff.Numerator = 0;
   end "=";
 
   function Numerator (A : Rational) return Number is
   begin
      return A.Numerator;
   end Numerator;
 
   function Denominator (A : Rational) return Number is
   begin
      return A.Denominator;
   end Denominator;
 
end Generic_Rational;
