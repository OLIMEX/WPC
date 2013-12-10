dict1 = {2:"abc", 3:"def", 4:"ghi", 5:"jkl", 6:"mno",7:"pqrs", 8:"tuv",
9:"wxyz" }

letter_to_digits = {}

for digit in dict1.keys():
   letters = dict1[digit]
   for lidx in range(len(letters)):
       letter = letters[lidx]
       letter_to_digits[letter] = (""+str(digit))*(lidx + 1)

def encode_letters(letters):
   """  
   >>> encode_letters("HELLO")
   '44 33 555 555 666'
   
   """
   encodings = []
   for letter in letters.lower():
      encodings.append(letter_to_digits.get(letter, '1'))
   return " ".join(encodings)

if __name__ == "__main__":
   print encode_letters("HELLO")
   print encode_letters("hello")
   print encode_letters("Thank you OLIMEX for a fun challenge and a great OLinuXino MICRO")
