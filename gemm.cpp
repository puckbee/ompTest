
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <stdio.h>
#include <omp.h>

#include <immintrin.h>

int main(int argc, char** argv)
{

    double* A = (double*) _mm_malloc ( sizeof(double) * D * (D+1), 64);
    double* B = (double*) _mm_malloc ( sizeof(double) * D * D, 64);
    double* C = (double*) _mm_malloc ( sizeof(double) * D * D, 64);


    for(int i=0; i< D*D; i++)
    {
//        A[i] = (double(i%100)/2) * (double(i%100)/2);
//        B[i] = (double(i%100)/4) * (double(i%100)/4);
//        C[i] = (double(i%100)/2);
        A[i] = i%2;
        B[i] = i%3;
        C[i] = 0;
    }


//  loop1 with automatic parallel pragma (collapse may cause write conflict, but normally fine.)
    #pragma omp parallel for
    for (int i=0; i<D; i++)
        for(int j=0; j<D; j++)
            for(int k=0; k<D; k++)
                C[i*D+j] += A[i*D+k] * B[k*D+j];
// end of loop1


/*
// loop2 with mannually blocking
    int Nthrds = omp_get_max_threads();
    
    int blockSize = D / Nthrds;

    #pragma omp parallel num_threads(Nthrds)
    {
      int idx = omp_get_thread_num();

        for (int i= idx * blockSize; i<(idx+1)*blockSize; i++)
            for(int j=0; j<D; j++)
                for(int k=0; k<D; k++)
                    C[i*D+j] += A[i*D+k] * B[k*D+j];
    }
//end of loop2
*/

/*    
//  loop3 with write confliction (the logic is wrong, just for demonstrating)
    #pragma omp parallel for
    for (int i=0; i<D; i++)
        for(int j=0; j<D; j++)
            for(int k=0; k<D; k++)
                C[i%2] += A[i*D+k] * B[k*D+j];
// end of loop3
*/
 
/*    
// loop4 without reduction (there are write conflict on 'sum', so the result would be wrong)
    double sum = 0;
    #pragma omp parallel for
    for(int i=0; i<D; i++)
        sum += i%10;
    printf(" sum = %f \n", sum);
 //end of loop4
*/

/*
// loop5 with reduction 
    double sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for(int i=0; i<D; i++)
        sum += i%10;
    printf(" sum = %f \n", sum);
 //end of loop5
*/

    printf(" C[0] = %f\n", C[0]);
}














