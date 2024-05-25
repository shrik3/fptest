/*
 * $Id: remquo.c 17183 2007-05-02 14:17:31Z lefevre $
 *
 * Test the quo value of the remquo() function.
 *
 * For gcc, compile with -std=c99 and link with -lm, e.g.
 *       gcc -Wall -O2 -std=c99 remquo.c -o remquo -lm
 */

#include <stdio.h>
#include <math.h>

static char *sign[2] = { "positive", "negative" };

int main (void)
{
  int sx, sy;
  double x, y;

  for (sy = 0; sy < 2; sy++)
    for (sx = 0; sx < 2; sx++)
      {
        printf ("\nx is %s, y is %s\nx =    ", sign[sx], sign[sy]);
        for (x = 0.0; x <= 16.0; x += 1.0)
          printf (" %3g", x);
        printf ("\n");
        for (y = 0.0; y <= 16.0; y += 1.0)
          {
            printf ("y = %2g:", y);
            for (x = 0.0; x <= 16.0; x += 1.0)
              {
                int quo = 99;
                remquo (sx ? -x : x, sy ? -y : y, &quo);
                printf (" %3d", quo);
              }
            printf ("\n");
          }
      }

  return 0;
}
