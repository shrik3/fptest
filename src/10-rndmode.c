/* $Id: rndmode.c 70589 2014-06-22 21:02:12Z vinc17/xvii $

Compare the timings with OPT = 0, 1 and 2 to measure the
fegetround/fesetround performance when the rounding mode
doesn't change. See thread:
  https://lists.debian.org/debian-devel/2012/07/msg00466.html
and in particular:
  https://lists.debian.org/debian-devel/2012/07/msg00747.html

Possible test:

for opt in 0 1 2
do
  gcc -O2 rndmode.c -o rndmode -lm -DOPT=$opt
  echo "OPT=$opt"
  for i in 0 1 2; do time ./rndmode; done
done

On a Debian/squeeze x86_64 Quad-Core AMD Opteron 8378 @ 2.40GHz machine
with libc6 2.11.3-3 and GCC 4.4.5: 4.62s / 8.92s / 4.72s

On a Debian/squeeze x86_64 Intel Xeon X5650 @ 2.67GHz machine
with libc6 2.11.3-3 and GCC 4.4.5: 3.22s / 4.69s / 3.51s

On a Debian/unstable x86_64 Intel Xeon E5520 @ 2.27GHz machine
with libc6 2.13-35 and GCC 4.7.1: 3.37s / 5.20s / 3.66s

On a Debian/unstable x86_64 Intel Core2 Duo P8600 @ 2.40GHz machine
with libc6 2.13-35 and GCC 4.7.1: 3.35s / 11.77s / 3.70s

On a Red Hat Fedora release 16 (Verne) POWER7 @ 3.55GHz machine
with glibc 2.14.90-24 and GCC 4.6.3: 7.29s / 11.16s / 7.86s
*/

#include <stdio.h>
#include <math.h>
#include <fenv.h>
#pragma STDC FENV_ACCESS ON

#ifndef N
#define N 100000000
#endif

int main (void)
{
  volatile double x = 1.0, y = 0.0;
  int i;

  for (i = 0; i < N; i++)
    {
#if OPT
      int r = fegetround();
#if OPT > 1
      if (r != FE_TONEAREST)
#endif
        fesetround (FE_TONEAREST);
#endif
      y += exp(x);
#if OPT
#if OPT > 1
      if (r != FE_TONEAREST)
#endif
        fesetround (r);
#endif
    }
  return y == 0.0;
}
