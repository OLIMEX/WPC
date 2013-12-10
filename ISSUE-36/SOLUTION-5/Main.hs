{-
WPC 36 - Text message converter.

Assuming that key 1 translates into a period and key 0 translates into a space.
Further assuming that key # makes the next character uppercase.

This rather convoluted Haskell program is meant as an exercise.
The obvious way would be to use a lookup table as in this C program

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* LUT[] = {
    "2","22","222",
    "3","33","333",
    "4","44","444",
    "5","55","555",
    "6","66","666",
    "7","77","777","7777",
    "8","88","888",
    "9","99","999","9999"
};

void convertline(char* aline)
{
    for (int i = 0; aline[i]; i++)
    {
        char c = aline[i];

        if (isupper(c))
        {
            printf("# ");
            c = tolower(c);
        }

        if ((c >= 'a') && (c <= 'z'))
            printf("%s ", LUT[c-97]);
        else if (c == ' ')
            printf("0 ");
        else if (c == '.')
            printf("1 ");
    }
}

int main()
{
    char *aline = NULL;
    size_t buflength = 0;
    size_t length;

    printf("Enter a string:");
    getline(&aline, &buflength, stdin);
    convertline(aline);
    printf("\n");

    free(aline);
    return 0;
}

-}
module Main where

import System.IO
import Data.Char
import Data.List
import Data.Maybe

{- | Align characters in groups of four -}
align :: Char -> String
align x
    | z == -50 || z == -64 = [x,x,x,x]
    | z < 16 && mod z 3 == 0 = [x,x]
    | z < 16 = [x]
    | z > 19 && z < 23 && mod (z-1) 3 == 0 = [x,x]
    | otherwise = [x]
    where z = ord x - 96

{- | Convert a single character to a series of keypresses -}
char2key :: Char -> String
char2key x
    | isUpper x =  "# " ++ mapped
    | otherwise = mapped
    where keys = ['1']++['2'..'9']++['0']
          chars = ['.']++['a'..'z']++[' ']
          mappedchars = concat $ map (align) chars
          charpos = fromJust (elemIndex (toLower x) mappedchars)
          index = div charpos 4
          count = mod charpos 4 + 1
          mapped = replicate count (keys !! index) ++ " "

{- | Convert a complete string -}
convert :: String -> String
convert x = concat $ map char2key x

main = do
    putStrLn "Enter a string:"
    input <- getLine
    putStrLn $ "Output is: " ++ convert input
