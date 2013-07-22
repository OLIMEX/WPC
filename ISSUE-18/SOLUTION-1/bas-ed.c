/* A tiny BASIC interpreter */
/* 
2013-07-21 by kantal59
   License for modifications: LGPL
   Compile: gcc -o bas-ed bas-ed.c

   OLIMEX WPC#18:
        Problem: BAS-INT is freeware tiny Basic interpreter with the bare minimum for BASIC scripting language. It works with external files only and is with Basic Stamp like syntax.
        The Challenge today is to write minimal console editor which to complement BAS-INT and to perform some very basic commands:
            List – list the program in memory with numbers
            Delete N(-M) – deletes line N or N to M from memory
            Insert N – inserts line on number N
            Run – runs the BASIC program in memory (this code is already available)
        if one wants to make it even more advanced he may make also the
            Edit N – prints the content of line N and allow it to be edited
        Remember this is console application and you have just serial in and serial out, no fancy graphics and windows in this editor.
    --------------------
    
    I hadn't much time, so this code isn't thoroughly tested. 
    The commands:
        list         lists all the lines
        list 5 10    lists lines from 5 up to 10
        list 5       lists the 5th line
        list 5 *     lists lines from 5 up to last line
        
        delete 5      delete the 5th line
        delete 5 10   delete the lines from 5 to 10
        
        insert 5: 100 FOR T = 1 TO I      inserts the given code before the 5th line
        append 100 FOR T = 1 TO I         appends the given code
        
        run      runs the code
        quit     quits the interpreter

    Usage: $> bas-ed  input_dev  ouput_dev  [ initial_code]
         E.g.: bas-ed  stdin stdout example.bas
               bas-ed /dev/ttyS0 /dev/ttyS1 example.bas  
     
    There are some problems with handling the different input/output devices.           
    It tested only when the stdin and stdout are on the same PC: 
            $> bas-ed  stdin stdout example.bas
            
    and with two different PC connected via serial port:                
        PC A) 
            stty -F /dev/ttyS0 raw 115200 crtscts
            ./bas-ed /dev/ttyS0 stdout bas-ex2.bas

        PC B) 
            stty -F /dev/ttyS0 raw 115200 crtscts                                       
            cat - >/dev/ttyS0
            
    The code modifications can be checked e.g. by 'meld' ( sudo apt-get install meld).

*/
#include "stdio.h"
#include "setjmp.h"
#include "math.h"
#include "ctype.h"
#include "stdlib.h"
#include "string.h"

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

void run();
char *next_line(char *pstart);
int count_lines();
int get_line(int num);
void print_lines( int first, int last);
void delete_lines( int first, int last);
int insert_line( int num, char *nstr);
void get_command();
void ok();
#define SLINE       256     // line max length
#define min(x,y)    (((x)<=(y))? (x):(y))
char line[ SLINE];

#define CMDSIZE     320
char cmd[ CMDSIZE];
int str_list_len, str_delete_len, str_append_len, str_insert_len, str_run_len, str_quit_len;
 
char *p_buf;

FILE *out, *inp;


main(argc, argv)
int argc;
char *argv[];
{
//  char in[80];
//  int answer;


    out= stdout;
    inp= stdin;

  /* allocate memory for the program */
  if(!(p_buf=(char *) malloc(PROG_SIZE))) {
    puts("allocation failure");
    exit(1);
  }
  
  
  *p_buf=0;
  if( argc <3){
    puts("Usage: $> bas-ed  input_dev  ouput_dev  [ initial_code]\n E.g.: bas-ed  stdin stdout example.bas\n bas-ed /dev/ttyS0 /dev/ttyS0 example.bas\n");
    exit(2);
  }
  
  if(argc==4){
      /* load an initial program if any */
    if(!load_program(p_buf,argv[3])) exit(1);
  }  

 if( strcmp( argv[1],argv[2])==0 ){
    if( !(inp=fopen(argv[1],"rwb")) ){ puts("input/ouput device open error"); exit(2); }
    out= inp;
 }
 else{
     if( strcmp(argv[1],"stdin")!=0 ) inp=fopen( argv[1], "rb");
     if( strcmp(argv[2],"stdout")!=0 ) out=fopen( argv[2], "wb");   
     if( !inp || !out ){ puts("device open error"); exit(3); }   
 }

  if(setjmp(e_buf)) exit(10); /* initialize the long jump buffer */
  
  fprintf( out,"lines= %d\n", count_lines());
     
  str_list_len=strlen("list"); str_delete_len=strlen("delete"); str_append_len=strlen("append"); str_insert_len=strlen("append"); str_run_len=strlen("run"); str_quit_len=strlen("quit");
  while(1){
       
        char *endptr, *ptr;
        int lno1, lno2;
        get_command();
        
        // list         lists all the lines
        // list 5 10    lists lines from 5 up to 10
        // list 5       lists the 5th line
        // list 5 *     lists lines from 5 up to last line
        
        if( strncasecmp("list", cmd, str_list_len)==0 ){
            ptr= cmd+str_list_len;
            lno1= strtol( ptr, &endptr, 10);
            if( ptr==endptr){ 
                print_lines(1,0);ok();
                continue;
            }
            ptr= endptr+strspn(endptr," \t");
            if( *ptr=='*'){
                print_lines(lno1,0);ok();
                continue;
            } 
            lno2= strtol( ptr=endptr, &endptr, 10);    
            if( ptr==endptr){ 
                print_lines(lno1,lno1);ok();
                continue;
            } 
            print_lines(lno1,lno2);ok();
            continue;            
        }
        
        
        // delete 5      delete the 5th line
        // delete 5 10   delete the lines from 5 to 10
        if( strncasecmp("delete", cmd, str_delete_len)==0 ){
            ptr= cmd+str_delete_len;
            lno1= strtol( ptr, &endptr, 10);
            if( ptr==endptr){ puts("\nERR: no line number"); continue; } // no line number: do nothing;
            
            lno2= strtol( ptr=endptr, &endptr, 10);    
            if( ptr==endptr){ 
                delete_lines(lno1,lno1);
                ok(); continue;
            } 
            delete_lines(lno1,lno2); ok();
            continue;            
        }
        
        // insert 5: 100 FOR T = 1 TO I      inserts the given code before the 5th line
        // append 100 FOR T = 1 TO I         appends the given code
        if( strncasecmp("insert", cmd, str_insert_len)==0 ){
            ptr= cmd+str_insert_len;
            lno1= strtol( ptr, &endptr, 10);
            if( ptr==endptr){ puts("\nERR: no line number"); continue; } // no line number: do nothing;
            ptr= endptr+strspn(endptr," \t");
            if( *ptr!=':' ){ puts("\nERR: missing ':' after the line number"); continue; }
            insert_line(lno1, ++ptr); ok();
            continue;            
        }
        
        if( strncasecmp("append", cmd, str_append_len)==0 ){
            insert_line( PROG_SIZE, cmd+str_append_len);
            ok(); continue;
        }
        
        // run      runs the code
        if( strncasecmp("run", cmd, str_run_len)==0 ){ run(); ok(); continue; } 
        
        // quit     quits the interpreter
        if( strncasecmp("quit", cmd, str_quit_len)==0 ){ free(p_buf); exit(0); } 
  
  
  }
  
  return(0);
}  

void run()
{
  char *t;

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
	  return;
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
    if( *p!='\r'){ p++; i++;}
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
      fprintf( out,"%s",token);
      len += strlen(token);
      get_token();
    }
    else { /* is expression */
      putback();
      get_exp(&answer);
      get_token();
      len += fprintf( out,"%d", answer);
    }
    last_delim = *token; 

    if(*token==';') {
      /* compute number of spaces to move to next tab */
      spaces = 8 - (len % 8); 
      len += spaces; /* add in the tabbing position */
      while(spaces) { 
	fprintf( out," ");
        spaces--;
      }
    }
    else if(*token==',') /* do nothing */;
    else if(tok!=EOL && tok!=FINISHED) serror(0); 
  } while (*token==';' || *token==',');

  if(tok==EOL || tok==FINISHED) {
    if(last_delim != ';' && last_delim!=',') fprintf( out,"\n");
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
    fprintf( out,"%s",token); /* if so, print it and check for comma */
    get_token();
    if(*token!=',') serror(1);
    get_token();
  }
  else fprintf( out,"? "); /* otherwise, prompt with / */
  var = toupper(*token)-'A'; /* get the input var */
  

//  scanf("%d", &i); /* read input */
  if( !fgets( str, 79, inp) ) str[0];
  i= strtol( str,NULL, 10);

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
  fprintf( out,"%s\n", e[error]); 
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

  if(*prog=='\n' ) { 
    ++prog;
    tok = EOL; *token='\n';
    token[1]=0;
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
    while(*prog!='"'&& *prog!='\n') *temp++=*prog++;
    if(*prog=='\n') serror(1);
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
  if(strchr(" ;,+-<>/*%^=()", c) || c=='\t' || c=='\n' || c==0) 
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


// Extensions to the original code

char *next_line(char *pstart)
{
    char *ptr;
    if( ! *(ptr=pstart) ) return( pstart);
    
    while( *ptr!='\n' && *ptr) ptr++;
    if( *ptr) return( ++ptr);
    return(ptr);
}

int count_lines()
{
    int n=0;
    char *ptr= p_buf;
    while( *ptr){ n++;  ptr=next_line( ptr);    }        
    return(n);     
}

int get_line( int num)
{
   int n,len;
   char *pend,*ptr;
   
   line[0]=0;
   if( num <=0 ) return(-1);
   ptr= p_buf;
   n=0;
   while( n<num-1 ){
        if( ! *(ptr=next_line(ptr)) ) break;
        n++; 
   }
   if( n< num-1 ) return(-1);
   pend=next_line(ptr);
   len= min( pend-ptr, SLINE-1);
   strncpy( line, ptr, len );
   line[len]=0;
   if( line[len-1]=='\n' ) line[len-1]=0;
   return(0);
}

void print_lines( int first, int last)
{
    int n;
    if(last==0) last=PROG_SIZE;
    for( n=first; n<=last; n++){
        if( get_line(n)!=0 ) return;
        fprintf( out,"%d: %s\n", n, line);
    }        
        
}

void delete_lines( int first, int last)
{
    int n=1;
    char *ptr, *pstart;
    
    if( *(ptr=p_buf)==0 ) return;
    if(last==0) last=PROG_SIZE;
    
    while( n<first){
        ptr=next_line(ptr);
        n++;
        if( !*ptr) break;
    }
    if( n< first ) return;
    pstart= ptr;
    
    while( n<last+1){
        ptr=next_line(ptr);
        n++;
        if( !*ptr) break;
    }
   memmove( pstart, ptr, strlen(ptr)+1);
}

int insert_line( int lno, char *nstr)
{
    int nlines, codelth, n, len;
    char *ptr;
    
    if( lno <=0) return(-1); // invalid line number
    nlines= count_lines();
    codelth= strlen( p_buf);    
    len= strlen(nstr);
    
    if( len+1 > PROG_SIZE-codelth ) return(-2); // not enough storage
    
    if( nlines< lno){   // append
        *(p_buf+codelth)='\n';
        strcpy( p_buf+codelth+1,nstr);
        return(0);
    }
    n=1;
    ptr= p_buf;
    while( n< lno){
        ptr=next_line(ptr);
        n++;
    }
    memmove( ptr+len+1,ptr, strlen(ptr)+1);
    strcpy( ptr, nstr);
    *(ptr+len)='\n';
    return(0);
}

void get_command()
{
    int len;
    if( !fgets( cmd, CMDSIZE-1, inp) ){ cmd[0]; return; }
    len= strlen( cmd);
    if( cmd[len-1]=='\n')  cmd[len-1]=0;  
}

void ok(){ fprintf(out,"\nOK\n"); }

