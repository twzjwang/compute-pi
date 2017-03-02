#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <sys/time.h>

double pi = 3.14159265359;

double montecarlo(long long int N)
{
    long long int i;
    long long int M = 0;
    double x,y;

    for (i = 0; i < N; i++) {
        x = (double) rand() / RAND_MAX;
        y = (double) rand() / RAND_MAX;
        if ( x * x + y * y < 1)
            M++;
    }
    return (double) M / N * 4;
}

void compute_by_clock(long long int N)
{
    double temp_pi;

    clock_t start = clock();
    temp_pi = montecarlo(N);
    clock_t finish = clock();

    double  duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("clock()\n");
    printf("pi = %lf\n", temp_pi);
    printf("%lf (s)\n\n", duration);
}

void compute_by_clockgettime(long long int N)
{
    struct timespec start;
    struct timespec finish;
    double temp_pi;

    clock_gettime(CLOCK_MONOTONIC, &start);
    temp_pi = montecarlo(N);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    double  duration = (finish.tv_sec - start.tv_sec)
                       + (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("clock_gettime()\n");
    printf("pi = %lf\n", temp_pi);
    printf("%lf (s)\n\n", duration);
}

void compute_by_time(long long int N)
{
    double temp_pi;

    time_t start = time(0);
    temp_pi = montecarlo(N);
    time_t finish = time(0);

    double  duration = (double)(finish - start);
    printf("time()\n");
    printf("pi = %lf\n", temp_pi);
    printf("%lf (s)\n\n", duration);
}

void compute_by_gettimeofday(long long int N)
{
    struct timeval start;
    struct timeval finish;
    double temp_pi;

    gettimeofday(&start,NULL);
    temp_pi = montecarlo(N);
    gettimeofday(&finish,NULL);

    double  duration = (finish.tv_sec - start.tv_sec)
                       + (finish.tv_usec - start.tv_usec) / 1000000.0;
    printf("gettimeofday()\n");
    printf("pi = %lf\n", temp_pi);
    printf("%lf (s)\n\n", duration);
}

int main()
{
    long long int N;
    struct timespec start;
    struct timespec finish;
    double temp_pi;
    double error;
    double duration;

    for (N = 1; N < 10000000000; N*=10) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        temp_pi = montecarlo(N);
        clock_gettime(CLOCK_MONOTONIC, &finish);
        error = (temp_pi < pi) ? (pi - temp_pi) : (temp_pi - pi);
        duration = (finish.tv_sec - start.tv_sec)
                   + (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
        printf("N = %lld\n%lf (s)\n", N, duration);
        printf("pi    = %lf\nerror = %lf\n\n", temp_pi, error);
    }
    return 0;
}
