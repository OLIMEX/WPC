#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int a =2;
  unsigned char *p = (char*)&a;
  if (*p > 0) {
    printf("Little endian\n");
  } else {
    printf("Big endian\n");
  }
return 0;
}
