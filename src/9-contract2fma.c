/* Test of the effect of the contraction to FMA.
 * Usage: contract2fma <double> ...
 *
 * This test program was originally written in 2008 by Vincent Lefevre.
 * It is in the public domain. Do whatever you want with it.
 *
 * More information on: http://www.vinc17.net/research/fptest.html
 */

#define SVNID "$Id: contract2fma.c 42710 2011-03-22 11:17:27Z vinc17/ypig $"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef FP_CONTRACT
#undef FP_CONTRACT
#define FP_CONTRACT "ON"
#pragma STDC FP_CONTRACT ON
#else
#define FP_CONTRACT "OFF"
#pragma STDC FP_CONTRACT OFF
#endif

static double fct (double a, double b)
{
  return a >= b ? sqrt (a * a - b * b) : 0;
}

/* "volatile" is needed to prevent icc from optimizing, and
   the "+ 0.0" is needed to prevent gcc from optimizing. */
static void test (volatile double x)
{
  printf ("test(%.20g) = %.20g\n", x, fct (x, x + 0.0));
}

int main (int argc, char **argv)
{
  int i;

  printf ("%s\n", SVNID);

  if (argc <= 1)
    {
      fprintf (stderr, "Usage: contract2fma <double> ...\n");
      return 1;
    }

  printf ("Test of a >= b ? sqrt (a * a - b * b) : 0 with FP_CONTRACT "
          FP_CONTRACT "\n");

  for (i = 1; i < argc; i++)
    test (atof (argv[i]));

  return 0;
}
