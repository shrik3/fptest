/* $Id: overflow.c 26269 2008-12-03 11:29:40Z vinc17/vin $
 *
 * Overflow behavior with gcc and intermediate extended precision.
 * Compile with: gcc -Wall -O2 overflow.c -o overflow -lm
 *   -DMODE=<value> [ -DCR=1 ]
 *
 * Results on x86 with gcc 4.0 and "overflow 2", depending on the -D options:
 *
 * With value = 1:
 * [1a] x = 3.595e+308   y = 3.595e+308   z = -3.595e+308
 *
 * With value = 2:
 * [1a] x = 3.595e+308   y = 3.595e+308   z = -3.595e+308
 * [1b] x = 3.595e+308   y = 3.595e+308   z = -3.595e+308
 *
 * With value = 3 and CR = 0:
 * [2a] x = 3.595e+308   y = 3.595e+308   z = -3.595e+308
 *
 * With value = 3 and CR = 1:
 * [2a] x = 1.798e+308   y = 1.798e+308   z = -inf
 *
 * With value = 4 and CR = 0:
 * [1a] x = 3.595e+308   y = 3.595e+308   z = -3.595e+308
 * [2a] x = 3.595e+308   y = 1.798e+308   z = -inf
 *
 * With value = 4 and CR = 1:
 * [1a] x = 3.595e+308   y = 3.595e+308   z = -1.798e+308
 * [2a] x = 3.595e+308   y = 1.798e+308   z = -1.798e+308
 *
 * With value = 5:
 * [1a] x = 3.595e+308   y = 1.798e+308   z = -1.798e+308
 * [1b] x = 3.595e+308   y = 1.798e+308   z = -1.798e+308
 * [2a] x = 1.798e+308   y = 1.798e+308   z = -1.798e+308
 *
 * About overflows, see also "traps1.c".
 *
 * This test program was originally written in 2005 by Vincent Lefevre.
 * It is in the public domain. Do whatever you want with it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <fenv.h>

#pragma STDC FENV_ACCESS ON

#define P1 ((MODE) % 3)
#define P2 ((MODE) / 3)

int main (int argc, char *argv[])
{
  double x, y, z;

  if (argc != 2)
    {
      fprintf (stderr, "Usage: overflow <double>\n");
      exit (1);
    }

  if (fesetround (FE_DOWNWARD))
    {
      fprintf (stderr, "Can't set rounding mode to FE_DOWNWARD\n");
      exit (1);
    }

  x = atof (argv[1]);
  x *= DBL_MAX;
  y = x + 0.0;
  z = x * -1.0;
#if P1
  printf ("[1a] x = %-12.4Lg y = %-12.4Lg z = %-12.4Lg\n",
          (long double) x, (long double) y, (long double) z);
#if P1 == 2
  printf ("[1b] x = %-12.4Lg y = %-12.4Lg z = %-12.4Lg\n",
          (long double) x, (long double) y, (long double) z);
#endif
#endif
#if CR
  printf ("\r");
#endif
  x += 0.0;
  y += 0.0;
  z += 0.0;
#if P2
  printf ("[2a] x = %-12.4Lg y = %-12.4Lg z = %-12.4Lg\n",
          (long double) x, (long double) y, (long double) z);
#if P2 == 2
  printf ("[2b] x = %-12.4Lg y = %-12.4Lg z = %-12.4Lg\n",
          (long double) x, (long double) y, (long double) z);
#endif
#endif
  return 0;
}
