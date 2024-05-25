/*
 * $Id: testlgamma.c 17124 2007-04-27 11:52:34Z lefevre $
 *
 * Test the lgamma() and lgamma_r() functions.
 *
 * For gcc, compile with -std=gnu99 and link with -lm, e.g.
 *       gcc -Wall -O2 -std=gnu99 testlgamma.c -o testlgamma -lm
 */

#include <stdio.h>
#include <math.h>

#ifndef NAN
#define NAN (0.0/0.0)
#endif

#ifndef INFINITY
#define INFINITY (1.0/0.0)
#endif

#ifndef NO_LGAMMA_R
double lgamma_r (double x, int *);
#endif

static void check (int ok, double y, double z, int sign)
{
  if (ok)
    printf ("  Got %g as expected", y);
  else
    printf ("  ERROR! Got %g instead of %g", y, z);
  printf (", and sign = %d.\n", sign);
}

static void test (double x)
{
  double y;
  int sign;

#ifndef NO_TGAMMA
  printf ("Checking tgamma on %g.\n", x);
  y = tgamma (x);
  check (x == 0 ? y == 1 / x : isnan (y), y,
         x == 0 ? 1 / x : NAN, signbit (y) ? -1 : 1);
#endif

  printf ("Checking lgamma on %g.\n", x);
  signgam = 17;
  y = lgamma (x);
  check (isnan (x) ? isnan (y) : y == INFINITY, y,
         isnan (x) ? NAN : INFINITY, signgam);

#ifndef NO_LGAMMA_R
  printf ("Checking lgamma_r on %g.\n", x);
  sign = 17;
  y = lgamma_r (x, &sign);
  check (isnan (x) ? isnan (y) : y == INFINITY, y,
         isnan (x) ? NAN : INFINITY, sign);
#endif
}

int main (void)
{
  test (+0.);
  putchar ('\n');
  test (-0.);
  putchar ('\n');
  test (-1.);
  putchar ('\n');
  test (-2.);
  putchar ('\n');
  test (-INFINITY);
  putchar ('\n');
  test (NAN);
  return 0;
}
