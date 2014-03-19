#include <stdio.h>

int main(void)
{
  int count = 0;
  int hours, mins;
  float seconds, crosstime;

  // Calculate in seconds - 43200 is number of seconds in 12 hours

  printf("Hands cross at:\n");
  for (int i = 0; i < 39600; i += 3600) {
    crosstime = i * 120.0 / 110.0;    // Derived from first principles
    hours = crosstime / 3600;
    crosstime -= hours * 3600;
    mins = crosstime/60.0;
    seconds = crosstime - (mins * 60);
    printf("\t%02d:%02d:%05.2f\n", hours, mins, seconds);
    count += 1;
  }
  printf("Count of crosses: %d\n", count);
}


