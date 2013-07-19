
/* A tiny BASIC interpreter */

#include "stdio.h"
#include "setjmp.h"
#include "math.h"
#include "ctype.h"
#include "stdlib.h"

#define NUM_LAB 100
#define LAB_LEN 10 
#define FOR_NEST 25
#define SUB_NEST 25
#define PROG_SIZE 10000

#define DELIMITER  1
#define VARIABLE  2
#define NUMBER    3
#define COMMAND   4
#define STRING	  5
#define QUOTE	  6

#define PRINT 1
#define INPUT 2
#define IF    3
#define THEN  4
#define FOR   5
#define NEXT  6
#define TO    7
#define GOTO  8
#define EOL   9
#define FINISHED  10
#define GOSUB 11
#define RETURN 12
#define END 13

char *prog;  /* holds expression to be analyzed */
jmp_buf e_buf; /* hold environment for longjmp() */

int variables[26]= {    /* 26 user variables,  A-Z */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0
};

struct commands { /* keyword lookup table */
  char command[20];
  char tok;
} table[] = { /* Commands must be entered lowercase */
  "print", PRINT, /* in this table. */
  "input", INPUT,
  "if", IF,
  "then", THEN,
  "goto", GOTO,
  "for", FOR,
  "next", NEXT,
  "to", TO,
  "gosub", GOSUB,
  "return", RETURN,
  "end", END,
  "", END  /* mark end of table */
};

char token[80];
char token_type, tok;

struct label {
  char name[LAB_LEN];
  char *p;  /* points to place to go in source file*/
};
struct label label_table[NUM_LAB];

char *find_label(), *gpop();

struct for_stack {
  int var; /* counter variable */
  int target;  /* target value */
  char *loc;
} fstack[FOR_NEST]; /* stack for FOR/NEXT loop */
struct for_stack fpop();

char *gstack[SUB_NEST];	/* stack for gosub */

int ftos;  /* index to top of FOR stack */
int gtos;  /* index to top of GOSUB stack */

void print(), scan_labels(), find_eol(), exec_goto();
void exec_if(), exec_for(), next(), fpush(), input();
void gosub(), greturn(), gpush(), label_init();
void serror(), get_exp(), putback();
void level2(), level3(), level4(), level5(), level6(), primitive();
void unary(), arith();

main(argc, argv)
int argc;
char *argv[];
{
  char in[80];
  int answer;
  char *p_buf;
  char *t;

  if(argc!=2) {
    printf("usage: run <filename>\n");
    exit(1);
  }

  /* allocate memory for the program */
  if(!(p_buf=(char *) malloc(PROG_SIZE))) {
    printf("allocation failure");
    exit(1);
  }
  
  /* load the program to execute */
  if(!load_program(p_buf,argv[1])) exit(1);

  if(setjmp(e_buf)) exit(1); /* initialize the long jump buffer */

  prog = p_buf;
  scan_labels(); /* find the labels in the program */
  ftos = 0; /* initialize the FOR stack index */
  gtos = 0; /* initialize the GOSUB stack index */
  do {
    token_type = get_token();
    /* check for assignment statement */
    if(token_type==VARIABLE) {
      putback(); /* return the var to the input stream */
      assignment(); /* must be assignment statement */
    }
    else /* is command */
      switch(tok) {
        case PRINT:
	  print();
  	  break;
        case GOTO:
	  exec_goto();
	  break;
	case IF:
	  exec_if();
	  break;
	case FOR:
	  exec_for();
	  break;
	case NEXT:
	  next();
	  break;
  	case INPUT:
	  input();
	  break;
        case GOSUB:
	  gosub();
	  break;
	case RETURN:
	  greturn();
	  break;
        case END:
	  exit(0);
      }
  } while (tok != FINISHED);
}

/* Load a program. */
load_program(p, fname)
char *p;
char *fname;
{
  FILE *fp;
  int i=0;

  if(!(fp=fopen(fname, "rb"))) return 0;
  
  i = 0;
  do {
    *p = getc(fp);
    p++; i++;
  } while(!feof(fp) && i<PROG_SIZE);
  *(p-2) = '\0'; /* null terminate the program */
  fclose(fp);
  return 1;
}

/* Assign a variable a value. */
assignment()
{
  int var, value;

  /* get the variable name */
  get_token();
  if(!isalpha(*token)) {
    serror(4);
    return;
  }

  var = toupper(*token)-'A';
 
  /* get the equals sign */
  get_token();
  if(*token!='=') {
    serror(3);
    return;
  }

  /* get the value to assign to var */
  get_exp(&value);

  /* assign the value */
  variables[var] = value;
}

/* Execute a simple version of the BASIC PRINT statement */
void print()
{
  int answer;
  int len=0, spaces;
  char last_delim;

  do {
    get_token(); /* get next list item */
    if(tok==EOL || tok==FINISHED) break;
    if(token_type==QUOTE) { /* is string */
      printf(token);
      len += strlen(token);
      get_token();
    }
    else { /* is expression */
      putback();
      get_exp(&answer);
      get_token();
      len += printf("%d", answer);
    }
    last_delim = *token; 

    if(*token==';') {
      /* compute number of spaces to move to next tab */
      spaces = 8 - (len % 8); 
      len += spaces; /* add in the tabbing position */
      while(spaces) { 
	printf(" ");
        spaces--;
      }
    }
    else if(*token==',') /* do nothing */;
    else if(tok!=EOL && tok!=FINISHED) serror(0); 
  } while (*token==';' || *token==',');

  if(tok==EOL || tok==FINISHED) {
    if(last_delim != ';' && last_delim!=',') printf("\n");
  }
  else serror(0); /* error is not , or ; */

}

/* Find all labels. */
void scan_labels()
{
  int addr;
  char *temp;

  label_init();  /* zero all labels */
  temp = prog;   /* save pointer to top of program */

  /* if the first token in the file is a label */
  get_token();
  if(token_type==NUMBER) {
    strcpy(label_table[0].name,token);
    label_table[0].p=prog;
  }

  find_eol();
  do {     
    get_token();
    if(token_type==NUMBER) {
      addr = get_next_label(token);
      if(addr==-1 || addr==-2) {
          (addr==-1) ?serror(5):serror(6);
      }
      strcpy(label_table[addr].name, token);
      label_table[addr].p = prog;  /* current point in program */
    }
    /* if not on a blank line, find next line */
    if(tok!=EOL) find_eol();
  } while(tok!=FINISHED);
  prog = temp;  /* restore to original */
}

/* Find the start of the next line. */
void find_eol()
{
  while(*prog!='\n'  && *prog!='\0') ++prog;
  if(*prog) prog++;
}

/* Return index of next free position in label array. 
   A -1 is returned if the array is full.
   A -2 is returned when duplicate label is found.
*/
get_next_label(s)
char *s;
{
  register int t;

  for(t=0;t<NUM_LAB;++t) {
    if(label_table[t].name[0]==0) return t;
    if(!strcmp(label_table[t].name,s)) return -2; /* dup */
  }

  return -1;
}

/* Find location of given label.  A null is returned if
   label is not found; otherwise a pointer to the position
   of the label is returned.
*/
char *find_label(s)
char *s;
{
  register int t;

  for(t=0; t<NUM_LAB; ++t) 
    if(!strcmp(label_table[t].name,s)) return label_table[t].p;
  return '\0'; /* error condition */
}

/* Execute a GOTO statement. */
void exec_goto()
{

  char *loc;

  get_token(); /* get label to go to */
  /* find the location of the label */
  loc = find_label(token);
  if(loc=='\0')
    serror(7); /* label not defined */

  else prog=loc;  /* start program running at that loc */
}

/* Initialize the array that holds the labels. 
   By convention, a null label name indicates that
   array position is unused.
*/
void label_init()
{
  register int t;

  for(t=0; t<NUM_LAB; ++t) label_table[t].name[0]='\0';
}

/* Execute an IF statement. */
void exec_if()
{
  int x , y, cond;
  char op;

  get_exp(&x); /* get left expression */

  get_token(); /* get the operator */
  if(!strchr("=<>", *token)) {
    serror(0); /* not a legal operator */
    return;
  }
  op=*token;

  get_exp(&y); /* get right expression */

  /* determine the outcome */
  cond = 0;
  switch(op) {
    case '<':
      if(x<y) cond=1;
      break;
    case '>':
      if(x>y) cond=1;
      break;
    case '=':
      if(x==y) cond=1;
      break;
  }
  if(cond) { /* is true so process target of IF */
    get_token();
    if(tok!=THEN) {
      serror(8);
      return;
    }/* else program execution starts on next line */
  }
  else find_eol(); /* find start of next line */
}

/* Execute a FOR loop. */
void exec_for()
{
  struct for_stack i;
  int value;

  get_token(); /* read the control variable */
  if(!isalpha(*token)) {
    serror(4);
    return;
  }

  i.var=toupper(*token)-'A'; /* save its index */

  get_token(); /* read the equals sign */
  if(*token!='=') {
    serror(3);
    return;
  }

  get_exp(&value); /* get initial value */

  variables[i.var]=value;

  get_token();
  if(tok!=TO) serror(9); /* read and discard the TO */

  get_exp(&i.target); /* get target value */

  /* if loop can execute at least once, push info on stack */
  if(value>=variables[i.var]) { 
    i.loc = prog;
    fpush(i);
  }
  else  /* otherwise, skip loop code altogether */
    while(tok!=NEXT) get_token();
}

/* Execute a NEXT statement. */
void next()
{
  struct for_stack i;

  i = fpop(); /* read the loop info */

  variables[i.var]++; /* increment control variable */
  if(variables[i.var]>i.target) return;  /* all done */
  fpush(i);  /* otherwise, restore the info */
  prog = i.loc;  /* loop */
}

/* Push function for the FOR stack. */
void fpush(i)
struct for_stack i;
{
   if(ftos>FOR_NEST)
    serror(10);

  fstack[ftos]=i;
  ftos++;
}

struct for_stack fpop()
{
  ftos--;
  if(ftos<0) serror(11);
  return(fstack[ftos]);
}

/* Execute a simple form of the BASIC INPUT command */
void input()
{
  char str[80], var;
  int i;

  get_token(); /* see if prompt string is present */
  if(token_type==QUOTE) {
    printf(token); /* if so, print it and check for comma */
    get_token();
    if(*token!=',') serror(1);
    get_token();
  }
  else printf("? "); /* otherwise, prompt with / */
  var = toupper(*token)-'A'; /* get the input var */

  scanf("%d", &i); /* read input */

  variables[var] = i; /* store it */
}

/* Execute a GOSUB command. */
void gosub()
{
  char *loc;

  get_token();
  /* find the label to call */
  loc = find_label(token);
  if(loc=='\0')
    serror(7); /* label not defined */
  else {
    gpush(prog); /* save place to return to */
    prog = loc;  /* start program running at that loc */
  }
}

/* Return from GOSUB. */
void greturn()
{
   prog = gpop();
}

/* GOSUB stack push function. */
void gpush(s)
char *s;
{
  gtos++;

  if(gtos==SUB_NEST) {
    serror(12);
    return;
  }

  gstack[gtos]=s;

}

/* GOSUB stack pop function. */
char *gpop()
{
  if(gtos==0) {
    serror(13);
    return 0;
  }

  return(gstack[gtos--]);
}

/* Entry point into parser. */
void get_exp(result)
int *result;
{
  get_token();
  if(!*token) {
    serror(2);
    return;
  }
  level2(result);
  putback(); /* return last token read to input stream */
}


/* display an error message */
void serror(error)
int error;
{
  static char *e[]= {   
    "syntax error", 
    "unbalanced parentheses", 
    "no expression present",
    "equals sign expected",
    "not a variable",
    "Label table full",
    "duplicate label",
    "undefined label",
    "THEN expected",
    "TO expected",
    "too many nested FOR loops",
    "NEXT without FOR",
    "too many nested GOSUBs",
    "RETURN without GOSUB"
  }; 
  printf("%s\n", e[error]); 
  longjmp(e_buf, 1); /* return to save point */
}

/* Get a token. */
get_token()
{

  register char *temp;

  token_type=0; tok=0;
  temp=token;

  if(*prog=='\0') { /* end of file */
    *token=0;
    tok = FINISHED;
    return(token_type=DELIMITER);
  }

  while(iswhite(*prog)) ++prog;  /* skip over white space */

  if(*prog=='\r') { /* crlf */
    ++prog; ++prog;
    tok = EOL; *token='\r';
    token[1]='\n'; token[2]=0;
    return (token_type = DELIMITER);
  }

  if(strchr("+-*^/%=;(),><", *prog)){ /* delimiter */
    *temp=*prog;
    prog++; /* advance to next position */
    temp++;
    *temp=0; 
    return (token_type=DELIMITER);
  }
    
  if(*prog=='"') { /* quoted string */
    prog++;
    while(*prog!='"'&& *prog!='\r') *temp++=*prog++;
    if(*prog=='\r') serror(1);
    prog++;*temp=0;
    return(token_type=QUOTE);
  }
  
  if(isdigit(*prog)) { /* number */
    while(!isdelim(*prog)) *temp++=*prog++;
    *temp = '\0';
    return(token_type = NUMBER);
  }

  if(isalpha(*prog)) { /* var or command */
    while(!isdelim(*prog)) *temp++=*prog++;
    token_type=STRING;
  }

  *temp = '\0';

  /* see if a string is a command or a variable */
  if(token_type==STRING) {
    tok=look_up(token); /* convert to internal rep */
    if(!tok) token_type = VARIABLE;
    else token_type = COMMAND; /* is a command */
  }
  return token_type;
}



/* Return a token to input stream. */
void putback() 
{

  char *t; 

  t = token; 
  for(; *t; t++) prog--; 
}

/* Look up a a token's internal representation in the
   token table.
*/
look_up(s)
char *s;
{
  register int i,j;
  char *p;

  /* convert to lowercase */
  p = s;
  while(*p){ *p = tolower(*p); p++; }

  /* see if token is in table */
  for(i=0; *table[i].command; i++)
      if(!strcmp(table[i].command, s)) return table[i].tok;
  return 0; /* unknown command */
}

/* Return true if c is a delimiter. */
isdelim(c)
char c; 
{
  if(strchr(" ;,+-<>/*%^=()", c) || c==9 || c=='\r' || c==0) 
    return 1;  
  return 0;
}

/* Return 1 if c is space or tab. */
iswhite(c)
char c;
{
  if(c==' ' || c=='\t') return 1;
  else return 0;
}



/*  Add or subtract two terms. */
void level2(result)
int *result;
{
  register char  op; 
  int hold; 

  level3(result); 
  while((op = *token) == '+' || op == '-') {
    get_token(); 
    level3(&hold); 
    arith(op, result, &hold);
  }
}

/* Multiply or divide two factors. */
void level3(result)
int *result;
{
  register char  op; 
  int hold;

  level4(result); 
  while((op = *token) == '*' || op == '/' || op == '%') {
    get_token(); 
    level4(&hold); 
    arith(op, result, &hold); 
  }
}

/* Process integer exponent. */
void level4(result)
int *result;
{
  int hold; 

  level5(result); 
  if(*token== '^') {
    get_token(); 
    level4(&hold); 
    arith('^', result, &hold); 
  }
}

/* Is a unary + or -. */
void level5(result)
int *result;
{
  register char  op; 

  op = 0; 
  if((token_type==DELIMITER) && *token=='+' || *token=='-') {
    op = *token; 
    get_token(); 
  }
  level6(result); 
  if(op)
    unary(op, result); 
}

/* Process parenthesized expression. */
void level6(result)
int *result;
{
  if((*token == '(') && (token_type == DELIMITER)) {
    get_token(); 
    level2(result); 
    if(*token != ')')
      serror(1);
    get_token(); 
  }
  else
    primitive(result);
}

/* Find value of number or variable. */
void primitive(result)
int *result;
{

  switch(token_type) {
  case VARIABLE:
    *result = find_var(token);
    get_token(); 
    return; 
  case NUMBER:
    *result = atoi(token);
    get_token();
    return;
  default:
    serror(0);
  }
}

/* Perform the specified arithmetic. */
void arith(o, r, h)
char o;
int *r, *h;
{
  register int t, ex;

  switch(o) {
    case '-':
      *r = *r-*h; 
      break; 
    case '+':
      *r = *r+*h; 
      break; 
    case '*':  
      *r = *r * *h; 
      break; 
    case '/':
      *r = (*r)/(*h);
      break; 
    case '%':
      t = (*r)/(*h); 
      *r = *r-(t*(*h)); 
      break; 
    case '^':
      ex = *r; 
      if(*h==0) {
        *r = 1; 
        break; 
      }
      for(t=*h-1; t>0; --t) *r = (*r) * ex;
      break;       
  }
}

/* Reverse the sign. */
void unary(o, r)
char o;
int *r;
{
  if(o=='-') *r = -(*r);
}

/* Find the value of a variable. */
int find_var(s)
char *s;
{
  if(!isalpha(*s)){
    serror(4); /* not a variable */
    return 0;
  }
  return variables[toupper(*token)-'A'];
}

