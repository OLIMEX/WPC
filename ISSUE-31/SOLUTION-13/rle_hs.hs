{-
 	Olimex WPC #31 - Run-length encoding and decoding (The Haskell version)

	This program reads a file and writes a run-length encoded or decoded version.

	There are two versions of the encoding / decoding routines.

	The first one always writes two bytes n and b. Byte n indicates the repeat count
	and b represents the value to be repeated.
	
	The second version writes just the value b if b is not repeated or writes b b n
	with n indicating the repeat count (with n >= 2). 

	Environment:
		Linux Mint 15
		The Glorious Glasgow Haskell Compilation System, version 7.6.2

	Compilation:
			compile to executable		: ghc rle_hs.hs
		or run the haskell interpreter	: runhaskell rle_hs.hs encode infile outfile

	Usage:
		To run-length encode "infile" into "outfile" : rle_hs encode infile outfile
		To decode "infile" into "outfile"            : rle_hs decode infile outfile

		alternative version:

		To run-length encode "infile" into "outfile" : rle_hs encode2 infile outfile
		To decode "infile" into "outfile"            : rle_hs decode2 infile outfile

-}

import Data.List
import System.Environment 
import qualified Data.ByteString.Lazy as B  
import Data.Word

{-
	Standard version: write bytes n and b with n indicating the number of
	times that b has to be repeated
-}
 
-- Convert tuples to array and split runs longer than 255
-- The result is an array [n,b] indicating that b is repeated n times 
detuple :: (Int, Word8) -> [Word8]
detuple (n,b)
	| n <= 255 = [(fromIntegral(n::Int))::Word8,b]
	| n > 255 = [255,b] ++ detuple (n-255, b)

-- Runlength encode
encode :: [Word8] -> [Word8]
encode x = concat ([detuple (length y, head y) | y <- group x]) 

-- Runlength decode
decode :: [Word8] -> [Word8]
decode [] = []
decode (x:xs) = (replicate ((fromIntegral(x::Word8))::Int) (head xs)) ++ (decode (tail xs)) 

-- Encode a file
encodeFile :: FilePath -> FilePath -> IO ()  
encodeFile source destination = do  
	contents <- B.readFile source  
	let encoded = B.pack (encode (B.unpack contents))
	B.writeFile destination encoded

-- Decode a file
decodeFile :: FilePath -> FilePath -> IO ()  
decodeFile source destination = do
	contents <- B.readFile source
	let decoded = B.pack (decode (B.unpack contents))
	B.writeFile destination decoded

{-
	Alternative version: 
		write byte b if b is not repeated
		write bytes b b n if b is repeated with n indicating the repeat count
-}

-- Convert tuples to array and split runs longer than 255
-- The result is
--     the array [b] if b is not repeated
--     the array [b,b,n] if b is repeated a times
detuple2 :: (Int, Word8) -> [Word8]
detuple2 (n,b)
	| n == 1 = [b]
	| n <= 255 = [b,b,(fromIntegral(n::Int))::Word8]
	| n > 255 = [b,b,255] ++ detuple2 (n-255, b)

-- Runlength encode - alternative version
encode2 :: [Word8] -> [Word8]
encode2 x = concat ([detuple2 (length y, head y) | y <- group x]) 

-- Runlength decode - alternative version
decode2 :: [Word8] -> [Word8]
decode2 [] = []
decode2 (x:xs)
	| xs == [] = [x]
	| x /= head xs = [x] ++ (decode2 xs)
	| x == head xs && [n] == [] = [x,x]
	| x == head xs = (replicate ((fromIntegral(n::Word8))::Int) x) ++ (decode2 (tail (tail xs))) 
	where n = head (tail xs)

-- Encode a file
encodeFile2 :: FilePath -> FilePath -> IO ()  
encodeFile2 source destination = do  
	contents <- B.readFile source  
	let encoded = B.pack (encode2 (B.unpack contents))
	B.writeFile destination encoded

-- Decode a file
decodeFile2 :: FilePath -> FilePath -> IO ()  
decodeFile2 source destination = do
	contents <- B.readFile source
	let decoded = B.pack (decode2 (B.unpack contents))
	B.writeFile destination decoded
   
main = do 
	args <- getArgs
	let (command:infile:outfile:_) = args
	if length args /= 3
		then do	
			putStrLn "\nThis program run-length encodes or decodes a file\n"
			putStrLn "Usage:"
			putStrLn "  To encode file \"infile\": rle_hs encode infile outfile"
			putStrLn "  To decode file \"infile\": rle_hs decode infile outfile"
			putStrLn "Alternative version:"
			putStrLn "  To encode file \"infile\": rle_hs encode2 infile outfile"
			putStrLn "  To decode file \"infile\": rle_hs decode2 infile outfile\n"
		else 
			case command of
				"encode"  -> encodeFile infile outfile
				"decode"  -> decodeFile infile outfile
				"encode2" -> encodeFile2 infile outfile
				"decode2" -> decodeFile2 infile outfile


