// WPC 66 - ASCII Christmas Tree
// Mint 15 - clang 3.2.1 - libcaca 0.99
// Compile: clang -lcaca wpc66.c -o wpc66

#include <caca.h>

int main(void)
{
  caca_canvas_t *cv;
  caca_display_t *dp;
  caca_event_t ev;

  // Create canvas and display
  cv = caca_create_canvas(100,80);
  if(!cv) return 1;

  dp = caca_create_display_with_driver(cv, "ncurses");
  if(!dp) return 1;

  caca_set_display_title(dp, "WPC 66");
  caca_set_color_ansi(cv, CACA_WHITE, CACA_BLACK);

  // Tree stump
  caca_fill_box (cv, 47, 50, 6, 4, '|');

  // Tree body
  caca_draw_thin_triangle (cv,50,10,10,50,90,50);

  // Pot
  caca_fill_triangle(cv, 35, 53, 40, 60, 40, 53, '@');
  caca_fill_box(cv, 40, 53, 19, 8, '@');
  caca_fill_triangle(cv, 59, 60, 64, 53, 59, 53, '@');

  // Balls
  int balls[] = {50, 25, 35, 35, 25, 43, 58, 32, 68, 41, 50, 46};
  for (int i = 0; i <= 10; i += 2)
      caca_draw_thin_ellipse(cv, balls[i], balls[i+1], 2, 2);

  // Sparkly stuff
  int sparks[] = {54, 20, 42, 30, 40, 45, 46, 38, 60, 43, 75, 48};
  for (int i = 0; i <= 10; i += 2)
  {
    caca_put_char(cv, sparks[i], sparks[i+1], '*');
    caca_put_char(cv, sparks[i]-1, sparks[i+1], '<');
    caca_put_char(cv, sparks[i]+1, sparks[i+1], '>');
    caca_put_char(cv, sparks[i], sparks[i+1]-1, '^');
    caca_put_char(cv, sparks[i], sparks[i+1]+1, 'v');
  }

  // Guirlandes
  caca_draw_thin_line(cv, 32, 44, 70, 35);
  caca_draw_thin_line(cv, 17, 49, 30, 46);
  caca_draw_thin_line(cv, 60, 47, 80, 43);
  caca_draw_thin_line(cv, 43, 35, 52, 33);
  caca_draw_thin_line(cv, 55, 28, 60, 27);
  caca_draw_thin_line(cv, 40, 25, 45, 24);

  // Star outline
  caca_fill_triangle(cv, 50, 16, 40, 10, 60, 10, ' ');
  int star_x[] = {50, 45, 40, 45, 40, 45, 50, 55, 60, 55, 60, 55, 50};
  int star_y[] = { 4,  7,  7, 10, 13, 13, 16, 13, 13, 10,  7,  7,  4};
  caca_draw_thin_polyline(cv, star_x, star_y, 12);

  // Inside of star
  int star[] = {50,8,50,9,50,10,50,11,50,12,49,9,48,9,51,9,52,9,49,10,51,10,49,11,48,11,51,11,52,11};
  for (int i = 0; i <= 29; i += 2)
      caca_put_char(cv, star[i], star[i+1], '*');

  // Display and wait for key press
  caca_refresh_display(dp);
  caca_get_event(dp, CACA_EVENT_KEY_PRESS, &ev, -1);
  caca_free_display(dp);
  return 0;
}

