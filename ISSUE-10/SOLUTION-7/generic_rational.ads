generic
   type Number is range <>;
package Generic_Rational is
   type Rational is private;
 
   function "abs"   (A : Rational) return Rational;
   function "+"     (A : Rational) return Rational;
   function "-"     (A : Rational) return Rational;
   function Inverse (A : Rational) return Rational;
 
   function "+" (A : Rational; B : Rational) return Rational;
   function "+" (A : Rational; B : Number  ) return Rational;
   function "+" (A : Number;   B : Rational) return Rational;
 
   function "-" (A : Rational; B : Rational) return Rational;
   function "-" (A : Rational; B : Number  ) return Rational;
   function "-" (A : Number;   B : Rational) return Rational;
 
   function "*" (A : Rational; B : Rational) return Rational;
   function "*" (A : Rational; B : Number  ) return Rational;
   function "*" (A : Number;   B : Rational) return Rational;
 
   function "/" (A : Rational; B : Rational) return Rational;
   function "/" (A : Rational; B : Number  ) return Rational;
   function "/" (A : Number;   B : Rational) return Rational;
   function "/" (A : Number;   B : Number)   return Rational;
 
   function ">"  (A : Rational; B : Rational) return Boolean;
   function ">"  (A : Number;   B : Rational) return Boolean;
   function ">"  (A : Rational; B : Number)   return Boolean;
 
   function "<"  (A : Rational; B : Rational) return Boolean;
   function "<"  (A : Number;   B : Rational) return Boolean;
   function "<"  (A : Rational; B : Number)   return Boolean;
 
   function ">=" (A : Rational; B : Rational) return Boolean;
   function ">=" (A : Number;   B : Rational) return Boolean;
   function ">=" (A : Rational; B : Number)   return Boolean;
 
   function "<=" (A : Rational; B : Rational) return Boolean;
   function "<=" (A : Number;   B : Rational) return Boolean;
   function "<=" (A : Rational; B : Number)   return Boolean;
 
   function "="  (A : Number;   B : Rational) return Boolean;
   function "="  (A : Rational; B : Number)   return Boolean;
 
   function Numerator   (A : Rational) return Number;
   function Denominator (A : Rational) return Number;
 
   Zero : constant Rational;
   One  : constant Rational;
private
   type Rational is record
      Numerator   : Number;
      Denominator : Number;
   end record;
 
   Zero : constant Rational := (0, 1);
   One  : constant Rational := (1, 1);
end Generic_Rational;
