#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_POINTS 100000000

int main() {

    printf("总点数 = %d\n", NUM_POINTS);

    srand(time(NULL));

    double start_time, end_time;
    double pi_estimate;
    int num_inside;

    // ============串行版本============
    start_time = omp_get_wtime();
    num_inside = 0;

    for (long i = 0; i < NUM_POINTS; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        if (x*x + y*y <= 1.0) {
            num_inside++;
        }
    }

    pi_estimate = 4.0 * num_inside / NUM_POINTS;
    end_time = omp_get_wtime();

    printf("\n串行版本：\n");
    printf("π估计值 = %.8f\n", pi_estimate);
    printf("计算时间 = %.6f 秒\n", end_time - start_time);



    // ============ TODO：并行版本 ============
    num_inside = 0;
    start_time = omp_get_wtime();

    #pragma omp parallel
    {
        //random seed for each thread
        unsigned int seed = time(NULL) ^ omp_get_thread_num();

        int local_inside = 0;

        #pragma omp for
        for(int i=0;i<NUM_POINTS;i++)
        {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;

            if(x*x + y*y <= 1.0)
            {
                local_inside++;
            }
        }

        #pragma omp critical
        {
            num_inside += local_inside;
        }
    }


    pi_estimate = 4.0 * num_inside / NUM_POINTS;
    end_time = omp_get_wtime();

    printf("\n并行版本：\n");
    printf("π估计值 = %.8f\n", pi_estimate);
    printf("计算时间 = %.6f 秒\n", end_time - start_time);

    // ============使用归约操作的并行版本============
    num_inside = 0;
    start_time = omp_get_wtime();

    #pragma omp parallel reduction(+:num_inside)
    {
        unsigned int seed = time(NULL) ^ omp_get_thread_num();
        #pragma omp for
        for (long i = 0; i < NUM_POINTS; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;

            if (x*x + y*y <= 1.0) {
                num_inside++;
            }
        }
    }
    pi_estimate = 4.0 * num_inside / NUM_POINTS;
    end_time = omp_get_wtime();

    printf("\n使用归约操作:\n");
    printf("π估计值 = %.8f\n", pi_estimate);
    printf("计算时间 = %.6f 秒\n", end_time - start_time);

    return 0;
}