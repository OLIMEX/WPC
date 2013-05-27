module Main where

import System.Environment

-- Integer implementation to do ceil(x/y)
roundUpDiv :: Integer -> Integer -> Integer
roundUpDiv x y = ((x-1) `div` y) + 1

{- We can use this greedy algorithm for Egyptian fractions, first
   described by Fibonacci, to transform rational numbers (num/den)
   into Egyptian fractions.

   x/y = 1 / ceil(y/x) + ((-y) mod x) / (y * ceil(y / x))

   This function returns a list of the denominators that make the
   Egyptian fractions.
-}
egyptianDenominators :: Integer -> Integer -> [Integer]
egyptianDenominators 0 den = []
egyptianDenominators 1 den = [den]
egyptianDenominators num den = ceilyx : otherDenominators
	where
		ceilyx = roundUpDiv den num
		remnum = (-den) `mod` num
		remden = den * (roundUpDiv den num)
		otherDenominators = egyptianDenominators remnum remden

-- Take two arguments and print the denominators
main = do
       args <- getArgs
       let a = read (args !! 0) :: Integer
       let b = read (args !! 1) :: Integer
       print $ egyptianDenominators a b