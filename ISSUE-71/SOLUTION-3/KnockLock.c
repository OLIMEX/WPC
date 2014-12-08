#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <memory.h>
#define LIMIT   64

double input_time(void) ;
int input_pattern(char*);
void check_knock(char,char* , char*,int,char);

int main()
{
    double time_short=0;
    double time_long=0;
    double delta , knock ;
    int dim_open,dim_lock;  // knock number
    char opn[LIMIT],lck[LIMIT] ;
    char opn_knock[LIMIT],lck_knock[LIMIT] ;
    int i; char ch;
    clock_t begin , end;

    printf ( "doubleclick <space> for define short time interval\n");
    time_short=input_time() ;
    printf ( "doubleclick <space> for define long time interval\n");
    time_long=input_time() ;
    printf ("time short [%f],time long [%f]\n",time_short,time_long);
    if ( time_short > time_long ) {
        printf ( "time short knock > time long knock\n");
        return 0 ;
    }
    delta = (time_long - time_short) / 2;
    printf ( "input pattern open(unlock)\n");
    dim_open = input_pattern(opn);
    printf ( "input pattern close(lock)\n");
    dim_lock = input_pattern(lck);
    memset ( opn_knock , 0 , LIMIT);
    memset ( lck_knock , 0 , LIMIT);
    /*
    for ( i=0;i < dim_open;i++)
        printf ( "%c ",opn[i]);
    printf("len %d\n",dim_open);
    for ( i=0;i < dim_lock;i++)
        printf ( "%c ",lck[i]);
    printf("len %d\n",dim_lock);
    */
    printf ( "testing\nc-clear data\nq-quit\n");
    for (i=0;;) {
        if( kbhit() ) {
            ch = getch();
            if ( ch == 'q') break ;
            if ( ch == 'c') {
                i=0;
                memset ( opn_knock , 0 , LIMIT);
                memset ( lck_knock , 0 , LIMIT);
                printf ( "clear\n");
                continue;
            }
            if ( i==1 ) {
                end = clock();
                knock = (double)(end - begin) / CLOCKS_PER_SEC;
                if ( abs ( knock - time_short) <= delta ){
                    check_knock('s',opn_knock , opn ,dim_open,'U');
                    check_knock('s',lck_knock , lck ,dim_lock,'L');
                    begin = end ;
                    continue ;
                }

                if ( abs ( knock - time_long) <= delta ){
                    check_knock('l',opn_knock , opn ,dim_open,'U');
                    check_knock('l',lck_knock , lck ,dim_lock,'L');
                    begin = end ;
                    continue ;
                }
                // clear
                i=0;
                memset ( opn_knock , 0 , LIMIT);
                memset ( lck_knock , 0 , LIMIT);
                continue ;

            }
            if ( i==0 ) {
                begin = clock();
                ++i;
            }
        }
    }
    return 0;
}

double input_time(void) {
    int i ;
    char ch;
    clock_t begin , end;
    double ret;
    for (i=0;;){
        if( kbhit() ) {
            ch = getch();
            if ( ch == ' ') {
                if ( i==1 ) { end = clock(); break;}
                if ( i==0 ) { begin = clock(); ++i;}
            }
        }
    }
    ret = (double)(end - begin) / CLOCKS_PER_SEC;
    return ret;
}

int input_pattern(char* s){
    char ch;
    int i;

    printf ("input s-short\ninput l-long\nq-quit\n");
    for (i=0;;){
        if( kbhit() ) {
            ch = getch();
            if ( ch == 's' || ch == 'l' )  {
                s[i++] = ch;
                printf("%c\n",ch);
            }
            if ( ch == 'q' )
                break ;
        }
    }
    return i ;
}

void check_knock(char type ,char* mask, char* flag,int len,char set ){
    int i;
    i = strlen ( mask ) ;
    if ( i >= len   )  return ;
    mask[i] = type ;
    if ( !strncmp ( mask , flag , len )) {
        if ( set == 'L')
          printf ( "CLOSE/LOCK\n" ) ;
        else
          printf ( "OPEN/UNLOCK\n" ) ;
    }
    return ;
}
