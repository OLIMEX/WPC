#include   <stdio.h>

     int        gint_target = 9808;
     int        gint_pages;

     int        gint_loop;
     int        gint_try;

     int        gint_start;

     char gchar_results[100];

void main(void)
{
     gint_start = 1;

     do
           {
           gint_loop = gint_start;
           gint_try = 0;
           gint_pages = 0;

           while(1)
                {
                gint_try += gint_loop;
                gint_pages++;

                if(gint_try >= gint_target)
                     {
                     break;
                     }

                gint_loop++;
                }

           if(gint_try == gint_target)
                {
                break;
                }

           gint_start++;
           } while(gint_start < gint_target);

     sprintf(gchar_results, "There are %d pages missing starting at page %d\r\n", gint_pages, gint_start);

     while(gint_try != gint_loop);
}



