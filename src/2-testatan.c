/*
 * $Id: testatan.c 70576 2014-06-22 19:31:05Z vinc17/xvii $
 *
 * Test the result of the atan() function. Showed a glibc bug on Alpha:
 *   https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=210613
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
      fprintf (stderr, "Usage: testatan <double>\n");
      exit (1);
    }

  x = atof (argv[1]);
  y = atan (x);

  out (x, "      x");
  out (y, "atan(x)");

  return 0;
}
