#include <stdlib.h>

#ifdef __cplusplus
using namespace std;
extern "C" {
#endif

// Dynamic programming algorithm for the 1d fused lasso problem
// (Ryan's implementation of Nick Johnson's algorithm)
void dp(int n, double *y, double lam, double *beta);

#ifdef __cplusplus
}
#endif
