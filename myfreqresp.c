/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * myfreqresp.c
 *
 * Code generation for function 'myfreqresp'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "myfreqresp.h"

/* Function Declarations */
static double rt_hypotd_snf(double u0, double u1);

/* Function Definitions */
static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  double b;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = b * sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

double myfreqresp(double N, const double D[2], double w)
{
  double bi;
  double z_re;
  double brm;
  double z_im;
  double s;
  bi = D[1] * w;
  if (bi == 0.0) {
    z_re = N / D[0];
    z_im = 0.0;
  } else if (D[0] == 0.0) {
    if (N == 0.0) {
      z_re = 0.0 / bi;
      z_im = 0.0;
    } else {
      z_re = 0.0;
      z_im = -(N / bi);
    }
  } else {
    brm = fabs(D[0]);
    z_im = fabs(bi);
    if (brm > z_im) {
      s = bi / D[0];
      z_im = D[0] + s * bi;
      z_re = (N + s * 0.0) / z_im;
      z_im = (0.0 - s * N) / z_im;
    } else if (z_im == brm) {
      if (D[0] > 0.0) {
        s = 0.5;
      } else {
        s = -0.5;
      }

      if (bi > 0.0) {
        z_im = 0.5;
      } else {
        z_im = -0.5;
      }

      z_re = (N * s + 0.0 * z_im) / brm;
      z_im = (0.0 * s - N * z_im) / brm;
    } else {
      s = D[0] / bi;
      z_im = bi + s * D[0];
      z_re = s * N / z_im;
      z_im = (s * 0.0 - N) / z_im;
    }
  }

  return rt_hypotd_snf(z_re, z_im);
}

/* End of code generation (myfreqresp.c) */
