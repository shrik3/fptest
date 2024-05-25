/* $Id: misc.c 42709 2011-03-22 11:12:38Z vinc17/ypig $
 *
 * Miscellaneous fma() tests.
 */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define WRONG(S,X,Y,Z,F,C)                                        \
  printf ("ERROR in test '" S "'!\nfma (%a, %a, %a)\n"            \
          "returned %a instead of %a.\n", X, Y, Z, F, C)

/* Modified Nelson H. F. Beebe's fma() test from stds-754 list, 2006-06-09 */
static int beebe (void)
{
  volatile double eps, e2, f, x, z;

  eps = DBL_EPSILON;
  e2 = eps * eps;
  x = 1.0 + eps;
  z = -1.0 - 2.0 * eps;
  f = fma (x, x, z);
  if (f != e2)
    {
      WRONG ("beebe", x, x, z, f, e2);
      return 1;
    }
  return 0;
}

static int overflowed_mul (void)
{
  volatile double x, f;

  x = DBL_MAX;
  f = fma (x, 2.0, -x);
  if (f != x)
    {
      WRONG ("overflowed_mul", x, 2.0, -x, f, x);
      return 1;
    }
  return 0;
}

int main (void)
{
  int err = 0;

  err += beebe ();
  err += overflowed_mul ();
  if (err == 0)
    printf ("OK\n");
  return err;
}
