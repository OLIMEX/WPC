#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/file.h>


int main (int argc, char* argv[])
{

  int fd  ;
  int lock ;
  char buf[128] ;

  if ( argc != 3 ) {
    printf ( "usage:proba  {1|2} filename\n") ;
    printf ( "1 - lock all file\n") ;
    printf ( "2 - lock first 5 bytes \n") ;
    return 1 ;
  }


  fd = open(argv[2], O_RDWR  | O_NDELAY | O_NONBLOCK | O_EXCL  , 0666 );
  if (fd == -1) {
        printf ( "can't open %s  , %s \n" , argv[2] , strerror(errno) )        ;
        return 1 ;
  }

  {}


   {                  }
       {
    }

}
