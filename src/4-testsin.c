/*
 * $Id: testsin.c 8526 2005-08-17 17:32:07Z lefevre $
 *
 * Test the result of the sin() function.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void out (double x, char *s)
{
  int exp;
  long long m;

  m = frexp (x, &exp) * 9007199254740992LL;
  printf ("%s = %-23.17g (mant: %lld/2^53, exp: %d)\n", s, x, m, exp);
}

int main (int argc, char *argv[])
{
  double x, y;

  if (argc != 2)
    {
      fprintf (stderr, "Usage: testsin <double>\n");
      exit (1);
    }

  x = atof (argv[1]);
  y = sin (x);

  out (x, "     x");
  out (y, "sin(x)");

  return 0;
}
