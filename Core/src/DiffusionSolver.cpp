/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*                                                                  */
/*     Aircraft Plume Chemistry, Emission and Microphysics Model    */
/*                             (APCEMM)                             */
/*                                                                  */
/* DiffusionSolver Program File                                     */
/*                                                                  */
/* Author               : Thibaud M. Fritz                          */
/* Time                 : 7/26/2018                                 */
/* File                 : DiffusionSolver.cpp                       */
/* Working directory    : /home/fritzt/APCEMM-SourceCode            */
/*                                                                  */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include <iostream>
#include <vector>
#include <complex>
#include <fftw3.h>

#include "Parameters.hpp"
#include "Interface.hpp"

typedef double Real;
typedef fftw_complex Complex;

void DiffusionSolver( std::vector<std::vector<double> >& vect, \
                      std::vector<std::vector<double> >& diffFactor, \
                      std::vector<std::vector<std::complex<double> > >& advFactor, \
                      const char* fileName_FFTW, \
                      const bool realInput )
{

    unsigned int i, j;

    /* If dealing with real input, set realInput to 1.
     * Output will be the same, the algorithm is roughly
     * 3 times after and requires ~75% of the original
     * memory requirement. */
        
    unsigned flags;
    /* Restoring plans from disk.
     * See following link for more information:
     * http://www.fftw.org/fftw3_doc/Wisdom.html#Wisdom */
    if ( FFTW_WISDOM && 0 ) { /* Under development ... */
        fftw_import_wisdom_from_filename( fileName_FFTW );
        flags = FFTW_WISDOM_ONLY | FFTW_PATIENT;
    }
    else
        flags = FFTW_ESTIMATE;


    /* Is data real? */
    if ( realInput ) { 
        /* After an r2c transform, the output is an ( NX * (NY/2 + 1) ) array */
        /* See the following link for more information:
         * http://www.fftw.org/fftw3_doc/Multi_002dDimensional-DFTs-of-Real-Data.html */
        const unsigned int NYH = NY/2 + 1;

        Complex *in_IFFT, *out_FFT;
        double *in_FFT, *out_IFFT;
        in_FFT   = (Real*) fftw_malloc(sizeof(Real) * NCELL);
        out_FFT  = (Complex*) fftw_malloc(sizeof(Complex) * NX * NYH);
    //  in_IFFT  = out_FFT .* diffFactor .* advFactor;
        in_IFFT  = (Complex*) fftw_malloc(sizeof(Complex) * NX * NYH);
        out_IFFT = (Real*) fftw_malloc(sizeof(Real) * NCELL);

        /* Allocate FFT plans */
        fftw_plan plan_FFT, plan_IFFT;

        /* Fill input */
        for ( i = 0; i < NX; i++ ) {
            for ( j = 0; j < NY; j++ )
                in_FFT[i*NY + j] = (Real) vect[j][i];
        }

        /* Define plan FFT */
        plan_FFT = fftw_plan_dft_r2c_2d( NX, NY, in_FFT, out_FFT, flags);

        /* Execute FFT */
        fftw_execute( plan_FFT );
    
        /* Fill */
        for ( i = 0; i < NX; i++ ) {
            for ( j = 0; j < NYH; j++ ) {
                in_IFFT[i*NYH + j][0] = ( out_FFT[i*NYH + j][0] * advFactor[j][i].real() \
                                        - out_FFT[i*NYH + j][1] * advFactor[j][i].imag() ) * ( diffFactor[j][i] );
                in_IFFT[i*NYH + j][1] = ( out_FFT[i*NYH + j][0] * advFactor[j][i].imag() \
                                        + out_FFT[i*NYH + j][1] * advFactor[j][i].real() ) * ( diffFactor[j][i] );
            }
        }

        /* Define plan IFFT */ 
        plan_IFFT = fftw_plan_dft_c2r_2d( NX, NY, in_IFFT, out_IFFT, flags);

        /* Execute IFFT */
        fftw_execute( plan_IFFT );

        /* Fill output */
        for ( i = 0; i < NX; i++ ) {
            for ( j = 0; j < NY; j++ ) 
                vect[j][i] = ( out_IFFT[i*NY+j] ) / ( Real( NCELL ) );
        }

        /* Destroy FFT plans */
        fftw_destroy_plan( plan_FFT  );
        fftw_destroy_plan( plan_IFFT );

        /* Free */
        fftw_free( in_FFT   ); 
        fftw_free( out_FFT  ); 
        fftw_free( in_IFFT  );
        fftw_free( out_IFFT );

    }
    /* Is data complex? */
    else {
    
        /* Dynamic allocation */
        Complex *in_FFT, *out_FFT, *in_IFFT, *out_IFFT;
        in_FFT   = (Complex*) fftw_malloc(sizeof(Complex) * NCELL);
        out_FFT  = (Complex*) fftw_malloc(sizeof(Complex) * NCELL);
    //  in_IFFT  = out_FFT .* diffFactor .* advFactor;
        in_IFFT  = (Complex*) fftw_malloc(sizeof(Complex) * NCELL);
        out_IFFT = (Complex*) fftw_malloc(sizeof(Complex) * NCELL);
    
        /* Allocate FFT plans */
        fftw_plan plan_FFT, plan_IFFT;

        /* Fill input */
        for ( i = 0; i < NX; i++ ) {
            for ( j = 0; j < NY; j++ )
                in_FFT[i*NY + j][0] = (double) vect[j][i];
        }

        /* Define plan FFT */
        plan_FFT  = fftw_plan_dft_2d( NX, NY, in_FFT, out_FFT, FFTW_FORWARD, flags);

        /* Execute FFT */
        fftw_execute( plan_FFT );
    
        /* Fill */
        for ( i = 0; i < NX; i++ ) {
            for ( j = 0; j < NY; j++ ) {
              in_IFFT[i*NY + j][0] = ( out_FFT[i*NY + j][0] * advFactor[j][i].real() \
                                     - out_FFT[i*NY + j][1] * advFactor[j][i].imag() ) * ( diffFactor[j][i] );
              in_IFFT[i*NY + j][1] = ( out_FFT[i*NY + j][0] * advFactor[j][i].imag() \
                                     + out_FFT[i*NY + j][1] * advFactor[j][i].real() ) * ( diffFactor[j][i] );
            }
         }

        /* Define plan IFFT */ 
        plan_IFFT = fftw_plan_dft_2d( NX, NY, in_IFFT, out_IFFT, FFTW_BACKWARD, flags);

        /* Execute IFFT */
        fftw_execute( plan_IFFT );

        /* Fill output */
        for ( i = 0; i < NX; i++ ) {
            for ( j = 0; j < NY; j++ ) 
                vect[j][i] = ( out_IFFT[i*NY+j][0] ) / ( Real( NCELL ) );
        }

        /* Destroy FFT plans */
        fftw_destroy_plan( plan_FFT  );
        fftw_destroy_plan( plan_IFFT );

        /* Free */
        fftw_free( in_FFT   ); 
        fftw_free( out_FFT  ); 
        fftw_free( in_IFFT  );
        fftw_free( out_IFFT );
    
    }

/*    1D EXAMPLE    */

//    fftw_complex *in_d, *out_d;
//    
//    in_d = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
//    out_d = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
//    for ( unsigned int i = 0; i < N; i++ ) {
//        in_d[i][0] = (double) i;
//        std::cout << "in_d[" << i << "] = " << *in_d[i] << std::endl;
//    }
//    
//    fftw_plan p;
//    
//    p = fftw_plan_dft_1d( N, &in_d[0], &out_d[0], FFTW_FORWARD, FFTW_ESTIMATE );
//    fftw_execute( p );
//
//    fftw_destroy_plan( p );
//
//    std::cout << "in = [ ";
//    for ( int i = 0; i < N; i++ )
//        std::cout << *in_d[i] << ", " ;
//    std::cout << "]" << std::endl;
//
//    std::cout << "out = [ ";
//    for ( int i = 0; i < N; i++ )
//        std::cout << *out_d[i] << ", " ;
//    std::cout << "]" << std::endl;
//
//    fftw_free(in_d);
//    fftw_free(out_d);

   
/*    2D EXAMPLE    */

//    fftw_complex *in, *out;

//    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N * N);
//    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N * N);
//    for ( unsigned int i = 0; i < N; i++ ) {
//        for ( unsigned int j = 0; j < N; j++ ) {
//            in[i*N + j][0] = (double) i+j;
//            in[i*N + j][1] = (double) 0.0;
//        }
//    }
//
//    fftw_plan p;
//
//    p = fftw_plan_dft_2d( N, N, in, out, FFTW_FORWARD, FFTW_ESTIMATE );
//    fftw_execute( p );
//
//    fftw_destroy_plan( p );

//    std::cout << "in = \n";
//    for ( unsigned int i = 0; i < N; i++ ) {
//        std::cout << "[ ";
//        for ( unsigned int j = 0; j < N; j++ )
//            std::cout << in[i*N+j][0] << ", " ;
//        std::cout << "]" << std::endl;
//    }
//
//    std::cout << "out = \n";
//    for ( unsigned int i = 0; i < N; i++ ) {
//        std::cout << "[ ";
//        for ( unsigned int j = 0; j < N; j++ )
//            std::cout << out[i*N+j][0] << ", " ;
//        std::cout << "]" << std::endl;
//    }
//
//    fftw_free(in);
//    fftw_free(out);

}