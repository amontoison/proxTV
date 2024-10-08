/**
    Headers for all the Total Variation algorithms and routines.

    @author Álvaro Barbero Jiménez
    @author Suvrit Sra
*/
#ifndef _TVOPT_H
#define _TVOPT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <stddef.h>

#include "general.h"
#include "LPopt.h"
#include "utils.h"
#include "condat_fast_tv.h"
#include "johnsonRyanTV.h"

/* TV-L1 solvers */

/* Stopping tolerance */
#define STOP_PN 1e-6
/* Minimum decrease */
#define SIGMA 0.0500
/* Maximum number of iterations */
#define MAX_ITERS_PN 100

/* TV-L2 solvers */

/* Stopping tolerances */
#define STOP_MS 1e-5 // Duality gap
#define STOP_MSSUB 1e-6 // Distance to boundary (prerequisite for termination)
/* Maximum number of iterations */
#define MAX_ITERS_MS 100

/* TV-Lp solvers */

/* Stopping tolerance */
#define STOP_TVLP 1e-5 // Duality gap
/* Maximum number of iterations */
#define MAX_ITERS_TVLP 10000
#define MAX_ITERS_TVLPFW 1000000
#define MAX_ITERS_TVLPGPFW 1000000
/* Maximum number of iterations without improvement */
#define MAX_NOIMP_TVLP 10
/* Accuracy of internal prox LP solver for GP algorithm */
#define OBJGAP_LPPROX_TVLP 1e-15
/* Lambda approximation steps */
#define LAMBDA_STEPS_TVLP 1
/* Reduction factor for initial lambda approximation step */
#define LAMBDA_REDUCTION_TVLP 1e3
/* Stopping tolerance in stepsize magnitude for FW algorithm */
#define STOP_STEP_TVLP_FW 1e-15
/* Numer of FW cycles per GP step in hybrid GP+FW method */
#define FW_CYCLES_TVLP 10
/* Maximum number of iterations without significant improvement in hybrid GP+FW method */
#define MAX_NOIMP_TVLP_GPFW (10*FW_CYCLES_TVLP)
/* Minimum improvement to be considered significant */
#define MIN_IMP_TVLP 1e-10
/* Enforced GP cycles in GP+FW method when ill-conditioning is detected */
#define ENFORCED_CYCLES_TVLP_GPFW 10

/* Multidimensional TV solvers */

/* Stopping tolerance */
#define STOP_PD 1e-6 // Mean absolute change in solution
/* Maximum number of iterations in Proximal Dykstra */
#define MAX_ITERS_PD 35
/* Maximum number of iterations in Condat's method */
#define MAX_ITERS_CONDAT 2500 //1000
/* Stopping tolerance in Condat's method */
#define STOP_CONDAT 0 //1e-6
/* Maximum number of iterations in Kolmogorov's method */
#define MAX_ITERS_KOLMOGOROV 2500
/* Stopping tolerance in Kolmogorov's method */
#define STOP_KOLMOGOROV 0 //1e-6
/* Douglas Rachford parameters */
#define MAX_ITERS_DR 35
/* Maximum number of iterations in Yang's method */
#define MAX_ITERS_YANG 35

#ifdef __cplusplus
extern "C" {
#endif

/*** Function headers ***/

/* General solvers */
int TV(double *y,double lambda,double *x,double *info,int n,double p,Workspace *ws);

/* TV-L1 solvers */
int PN_TV1(double *y,double lambda,double *x,double *info,int n,double sigma,Workspace *ws);
int linearizedTautString_TV1(double *y,double lambda,double *x,int n);
int classicTautString_TV1(double *signal, int n, double lam, double *prox);
void hybridTautString_TV1(double *y, int n, double lambda, double *x);
void hybridTautString_TV1_custom(double *y, int n, double lambda, double *x, double backtracksexp);
int classicTautString_TV1_offset(double *signal, int n, double lam, double *prox, double offset); //Inner method
void SolveTVConvexQuadratic_a1_nw(int n, double* b, double w, double* solution);

/* Weighted TV-L1 solvers */
int PN_TV1_Weighted(double* Y, double* W, double* X, double* info, int n, double sigma, Workspace* ws);
int tautString_TV1_Weighted(double *y,double* lambda,double *x,int n);
int PN_TV1_Trend2_Weighted(double* Y, double* W, double* X, double* info, int n, double sigma, Workspace* ws);
void SolveTVConvexQuadratic_a1(int n, double* b, double* w, double* solution);

/* TV-L2 solvers */
int more_TV2(double *y,double lambda,double *x,double *info,int n);
int morePG_TV2(double *y,double lambda,double *x,double *info,int n,Workspace *ws);
int PG_TV2(double *y,double lambda,double *x,double *info,int n);

/* Weighted TV-L2 solvers */
int DR2L1W_TV(size_t M, size_t N, double*unary, double*W1, double*W2, double*s, int nThreads, int maxit, double* info);

/* TV-Lp solvers */
int GP_TVp(double *y,double lambda,double *x,double *info,int n,double p,Workspace *ws);
int OGP_TVp(double *y,double lambda,double *x,double *info,int n,double p,Workspace *ws);
int FISTA_TVp(double *y,double lambda,double *x,double *info,int n,double p,Workspace *ws);
int FW_TVp(double *y,double lambda,double *x,double *info,int n,double p,Workspace *ws);
int GPFW_TVp(double *y,double lambda,double *x,double *info,int n,double p,Workspace *ws);

/* 2-dimensional TV solvers */
int PD2_TV(double *y,double *lambdas,double *norms,double *dims,double *x,double *info,int *ns,int nds,int npen,int ncores,int maxIters);
int proxDykstraTV2DWeighted(double* y, double* W, double* x,int* ns, int nds, double* info,int ncores,int maxIters);
int DR2_TV(size_t M, size_t N, double*unary, double W1, double W2, double norm1, double norm2, double*s, int nThreads, int maxit, double* info);
int CondatChambollePock2_TV(size_t M, size_t N, double*Y, double lambda, double*X, short alg, int maxit, double* info);
int Yang2_TV(size_t M, size_t N, double*Y, double lambda, double*X, int maxit, double* info);
int Kolmogorov2_TV(size_t M, size_t N, double*Y, double lambda, double*X, int maxit, double* info);

/* 3-dimensional TV solvers */
int Yang3_TV(size_t M, size_t N, size_t O, double*Y, double lambda, double*X, int maxit, double* info);

/* General-dimension TV solvers */
int PD_TV(double *y,double *lambdas,double *norms,double *dims,double *x,double *info,int *ns,int nds,int npen,int ncores,int maxIters);
int PDR_TV(double *y,double *lambdas,double *norms,double *dims,double *x,double *info,int *ns,int nds,int npen,int ncores,int maxIters);

#ifdef __cplusplus
}
#endif

#endif

