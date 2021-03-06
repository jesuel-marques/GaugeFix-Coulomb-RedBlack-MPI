#ifndef GAUGEFIXING_H
#define GAUGEFIXING_H

typedef enum {R, S, T} submatrix;

void SU3_update_global_U_G(mtrx_3x3 * restrict U, mtrx_3x3 * restrict G);

double SU3_calculate_e2(mtrx_3x3 * restrict U);

unsigned SU3_gauge_fix(mtrx_3x3 * restrict U,  mtrx_3x3 * restrict G, const unsigned short config);

void init_gauge_transformation(mtrx_3x3 * restrict G);

#endif