/* Copyright A.Couarraze & N.Aguirre */
/* Build with gcc -o hangman -Wall -ggdb -O0 -g3 hangman.c `pkg-config eina --cflags --libs` */
/* Install EFL for eina lib : on ubuntu sudo apt-add-repository ppa:efl/trunk && sudo apt-get update && sudo apt-get install libeina-dev */
/* Execute like this : ./hangman wordslist/ */
/* Excecute with stat and words list : ./hangman wordslist/  1 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Eina.h>

#define MAX(a,b) ((a) > (b) ? a : b)

/* Player can tries only 10 times */
#define LIFE_MAX 10

static char *guess = NULL;
static int guess_size = 0;
static char *propositions = NULL;
static int life = LIFE_MAX;
static int print_stats = 0;
static Eina_List *words_list = NULL;

char *words_list_directory = NULL;

/* The player enter the letter he wants */
static char _choose_a_char(void)
{
  int c;

  printf("Please enter a letter :");
  do 
    {
      c=getchar();
      getchar();
    }while (c <= 'a' && c >= 'z');

  return (char)c;
}

/* Read the files on the disk, should be :
 * words_list_directory/A Words.txt
 * words_list_directory/B Words.txt
 * ...
 * words_list_directory/Z Words.txt
 * Words must be seperated by '\n' char
 */
static void init_list(void)
{
  int i;
  FILE *fp;
  char tmp[4096];
  int lines = 0;
  for (i = 'A' ; i <= 'Z'; i++)
    {
      char str[16];
      snprintf(tmp, sizeof(tmp), "%s/%c Words.txt", words_list_directory, i); 
      fp = fopen(tmp, "r");
      while(fgets(str,sizeof(str),fp) != NULL)
	{
	  int len = strlen(str)-1;

	  if (len != guess_size)
	    continue;

	  lines ++;

	  if(str[len] == '\n') 
	    str[len] = 0;
	  words_list = eina_list_append(words_list, eina_stringshare_add(str));

	}
    }
}

/* Returns the the occurence of the char c in the word str. 
 * Pos contains the last known postion of the letter in the word 
 */
static char _word_contains(const char *str, char c, int *pos)
{
  int i;
  int occ = 0;

  for (i = 0; i < strlen(str); i++)
    if (str[i] == c)
      {
	occ++;
	if (pos) *pos = i;
      }

  return occ;
}


/* Black Magic function 
 * We decide here to never choose a word .
 * We compute the number of words wich doesn't contains the letter, 
 * and the number of words wich contains it at a specific position.
 * We look at the highest number, and we keep these list of words.
 * If a letter occurs two or more times in the words, we decides that's
 * it's too easy for the player, so we remove that possibility.
 */
static int _update_list(char c)
{
  unsigned char found = 0;
  int i;
  Eina_List *l;
  const char *word;
  int* stats;
  int max;
  Eina_List *tmp_list;
  int pos = 0;

  stats = calloc(guess_size + 1, sizeof(int));

  /* fill stats, 
   * stats[0] == number of words in the list wich doesn't contains the letter c
   * stats[1] == number of words in the list which contains the letter C at first position, and only at this position 
   * stats[X] == number of words which contains the letter C at Xth position, and only at this position  
   */ 

  EINA_LIST_FOREACH(words_list, l, word)
    {
      found = _word_contains(word, c, &pos);
      if (!found)
       stats[0]++;
      else if (found == 1)
	stats[pos+1]++;
    }

  /* Find where we found the hightest score */
  max = 0;
  pos = -1;
  for (i = 0; i < guess_size + 1; i++)
    {
      if (stats[i] > max)
	{
	  max = stats[i];
	  pos = i;
	}
    }

  /* Here pos contains the position in the word where the letter c appears the most 
   * pos == -1 : specific case where the player is right  :(
   * pos == 0 : there is more words which doesn't contains the letter c than words containing it at a dedicated position 
   * pos == X : there is more words which contains the letter at the Xth  position than those who doesn't contain it (or less thant at another position) 
   */

  word = eina_list_nth(words_list, 0);
  if (pos == -1)
    {
      for (i = 0; i < guess_size; i++)
	if (word[i] == c)
	  guess[i] = c;
      return 1;
    }

  tmp_list = words_list;
  words_list = NULL;


  /* For each elements in the previous list */
  EINA_LIST_FREE(tmp_list, word)
    {
      /* Current word contains the letter c, and how many times ? */
      found = _word_contains(word, c, NULL);

      /* if C is not found and pos is == 0, the list contains all words that doesn't contains c */
      if (!found && !pos)
	words_list = eina_list_append(words_list, eina_stringshare_add(word));
      /* if c is found only once and we find c at position pos, we add these words to the list*/
      else if (found == 1 && (word[pos - 1] == c))
	{  
	    words_list = eina_list_append(words_list, eina_stringshare_add(word));
	}
      /* Free removed words */
      eina_stringshare_del(word);
    }

  /* If pos is not NUL, we let the player win this time, so let it say where the right letter is */
  if (pos)
    guess[pos - 1] = c;

  if (print_stats)
    EINA_LIST_FOREACH(words_list, l, word)
      printf("word : %s\n", word);
 
  for (i = 0; i < guess_size + 1; i++)
    {
      if (print_stats)
	printf("[%*d] %*d words\n", 2, i, 10, stats[i]);
    }
  if (print_stats)
    printf("Stats : \n------------\n");

  free(stats);
  /* return 1 if the player win these time, 0 otherwise */
  return !!pos;
}

static void usage(int argc, char **argv)
{
  printf("Usage : %s words_list_directory\n", argv[0]);
  printf("words_list_directory must contains LF seperated files. These files must be named like that : A Words.txt, B Words.txt .... Z Words.txt\n");
  printf("Usage Example %s wordslist\n", argv[0]);
}

int main(int argc, char **argv)
{
  char c;
  char *word;

  eina_init();

  printf("hangman game. By A.Couarraze & N.Aguirre. (C) 2013\n");

  if (argc < 2)
    {
      usage(argc, argv);
      return EXIT_FAILURE;
    }
  else if (argc == 3)
    print_stats = atoi(argv[2]);

    words_list_directory = strdup(argv[1]);
  
  
  srand(time(NULL));
  /* Let choose a random size of words between 4 and 10 letters */
  guess_size = (rand() % 6) + 4;
  guess = calloc(guess_size + 1, sizeof(char));
  memset(guess, '-', guess_size);
  propositions = calloc(LIFE_MAX + 1, sizeof(char));
  
  /* Read the files on disk, and create the initial list of words */
  init_list();

  life = LIFE_MAX;
  while(life)
    {
      printf("remaining points of life : %d | %s\n", life, guess);
      /* Let the player enter the letter */
      c = _choose_a_char();
      /* Try to see if the entered letter has been already played */
      if (_word_contains(propositions, c, NULL))
	{
	  /* And it's the case */
	  printf("Hey what are you doing ?!, you already entered that letter. You should eat spinach, it's really good for memory ....\n");
	  continue;
	}
      else
	{
	  /* Nope, save it */
	  propositions[strlen(propositions)] = c;
	}
    
      /* It's here the magic happens */
      if (!_update_list(c))
	life--;
      
      /* if the guess words doesn't contains -, the player win !*/
      if (!_word_contains(guess, '-', NULL))
	{
	  printf("What ? You Won ? Incredible, i should be the worst computer ever build. Or you are maybe a a computer as well ? I can't believe in a human victory !\n");
	  break;
	}
    }


  if (!life)
    {
      int n = rand() % eina_list_count(words_list);
      printf("The word i choose (or not) was : %s \n", (char*)eina_list_nth(words_list, n));
      printf("You loose, but that's normal, you're only a poor human. Go play with your dolls, The hangman game is definitely not for you.\n");
    }
  
  EINA_LIST_FREE(words_list, word)
    eina_stringshare_del(word);

  free (words_list_directory);
  free(guess);
  free(propositions);
  printf("Bye Bye! I hope that i will kill you again soon!\n");
  return EXIT_SUCCESS;
}
