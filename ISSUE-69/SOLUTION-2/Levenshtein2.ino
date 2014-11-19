/*
Weekend Programming Challenge – Week #69 Levenshtein Distance
Problem:
Levenshtein Distance  is string metrics for measuring the difference between two sequences.
Make code which inputs two strings and calculate Levenshtein Distance between them.

Code based on: http://www.lemoda.net/c/levenshtein/
and modified for Arduino by: Javier Vela

What is Levenshtein Distance?
Levenshtein distance (or edit distance) between two strings is the number of deletions, insertions, or substitutions required to transform source string into target string.
For example, if source is "book" and target is "back", to transform "book" to "back" you will need to change first "o" to "a", second "o" to "c", without additional deletions and insertions, thus, levenshtein distance will be 2.
Levenshtein distance is named after the Russian scientist Vladimir Levenshtein, who devised the algorithm in 1965.
This has a wide range of applications, for instance, spell checkers, correction systems for optical character recognition, etc.
You can find more information in: http://es.wikipedia.org/wiki/Distancia_de_Levenshtein
*/


void setup()
{
  String palabra1, palabra2;
  int len1, len2, d;

  Serial.begin(9600);
  Serial.println("Welcome Levenshtein calculator");

  Serial.println("\nPlease, insert the first word: ");
  while (!Serial.available()) //Wait until something is written in the serial port 
  delay(100);
  while (Serial.available() > 0)//Reading the message from the serial port
      palabra1.concat((char)Serial.read());
  Serial.print(" -The first word is: "); Serial.println(palabra1);
  len1 = palabra1.length();
  Serial.print(" -Length: "); Serial.println(len1);

  Serial.println("\nPlease, insert the second word: ");
  while (!Serial.available()) //Wait until something is written in the serial port    
  delay(100);
  while (Serial.available() > 0)//Reading the message from the serial port
      palabra2.concat((char)Serial.read());
  Serial.print(" -The second word is: "); Serial.println(palabra2);
  len2 = palabra2.length();
  //len2 = strlen (word2);
  Serial.print(" -Length: "); Serial.println(len2);

  d = distance (palabra1, len1, palabra2, len2);
  Serial.print ("\nLevenshtein Distance between '"+palabra1+"' and '"+palabra2 + " is: " +d);
}

void loop()
{

}


static int distance (String palabra1, int len1, String palabra2, int len2)
{
  int matrix[len1 + 1][len2 + 1];
  int i;
  for (i = 0; i <= len1; i++)    matrix[i][0] = i;
  for (i = 0; i <= len2; i++)    matrix[0][i] = i;
  for (i = 1; i <= len1; i++)
  {
    int j;
    char c1;
    c1 = palabra1.charAt(i-1);
    for (j = 1; j <= len2; j++)
    {
      char c2;
      c2 = palabra2.charAt(j-1);
      if (c1 == c2)
      {
        matrix[i][j] = matrix[i - 1][j - 1];
      }
      else
      {
        int delet = matrix[i - 1][j] + 1;
        int insert = matrix[i][j - 1] + 1;
        int substitute = matrix[i - 1][j - 1] + 1;
        int minimum = delet;
        if (insert < minimum)      minimum = insert;
        if (substitute < minimum)  minimum = substitute;
        matrix[i][j] = minimum;
      }
    }
  }
  return matrix[len1][len2];
}

