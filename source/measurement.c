#include "../SU3_parameters.h"

#include <stdio.h>
#include <complex.h>
#include <omp.h>

#include "lattice.h"
#include "SU3_ops.h"

double SU3_re_tr_plaquette(matrix_3x3_double *U, const pos_vec position, const lorentz_index mu, const lorentz_index nu){
	
    matrix_3x3_double plaquette;

    matrix_3x3_double ua;
    matrix_3x3_double ub;
    matrix_3x3_double uc;
    matrix_3x3_double ud;

    pos_vec position_plus_mu = hop_position_positive(position, mu);

    get_link_matrix(U, position,                                    mu, FRONT, &ua);
    get_link_matrix(U, position_plus_mu,                            nu, FRONT, &ub);
    get_link_matrix(U, hop_position_positive(position_plus_mu, nu), mu, REAR , &uc);
    get_link_matrix(U, hop_position_positive(position, nu),         nu, REAR , &ud);

	product_four_3x3(&ua, &ub, &uc, &ud, &plaquette);

    // printf("%lf\n", creal(trace_3x3(plaquette)));
    // getchar();

    return (double)creal(trace_3x3(&plaquette))/Nc;

}

double spatial_plaquette_average(matrix_3x3_double * U){
    double plaq_ave = 0.0;


    #pragma omp parallel for reduction (+:plaq_ave) num_threads(NUM_THREADS) schedule(dynamic) 
        // Paralelizing by slicing the time extent
        for (pos_index t = 0; t < Nt; t++) {

            pos_vec position;

            position.t = t;
            double plaq_ave_slice = 0.0;

            for (position.k = 0; position.k < Nxyz; position.k++) {
                for (position.j = 0; position.j < Nxyz; position.j++) {
                    for (position.i = 0; position.i < Nxyz; position.i++) {
                        for (lorentz_index mu = 0; mu < d-1; mu++){
                            for (lorentz_index nu = 0; nu < d-1; nu++){
                                if( mu < nu){
                                    plaq_ave_slice += SU3_re_tr_plaquette(U, position, mu, nu);                                    
                                
                                }
                            }
                        
                        }
                    }
                }
            }

            plaq_ave += plaq_ave_slice;

        }

    plaq_ave /= (double)((d - 1.0) * Volume);

    return plaq_ave;
}

double temporal_plaquette_average(matrix_3x3_double * U){
    double plaq_ave = 0.0;


    #pragma omp parallel for reduction (+:plaq_ave) num_threads(NUM_THREADS) schedule(dynamic) 
        // Paralelizing by slicing the time extent
        for (pos_index t = 0; t < Nt; t++) {

            pos_vec position;

            position.t = t;
            double plaq_ave_slice = 0.0;

            for (position.k = 0; position.k < Nxyz; position.k++) {
                for (position.j = 0; position.j < Nxyz; position.j++) {
                    for (position.i = 0; position.i < Nxyz; position.i++) {
                        for (lorentz_index mu = 0; mu < d-1; mu++){
                     
                                plaq_ave_slice += SU3_re_tr_plaquette(U, position, t_index, mu);
                     
                        }    
                    }
                }
            }

            plaq_ave += plaq_ave_slice;

        }

    plaq_ave /= (double)((d - 1.0) * Volume);

    return plaq_ave;
}