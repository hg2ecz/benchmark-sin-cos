#include "benchmark-rotate-algs.h"

#include <time.h>
#include <stdio.h>

static struct timespec gstart, gend;

void t_start() {
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
}

unsigned long long t_end(const char *txt) {
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);
    unsigned long long nsec = 1000*1000*1000*(gend.tv_sec - gstart.tv_sec) + gend.tv_nsec - gstart.tv_nsec;
    //if (offset > 0) printf("%7.2f (%7.2f) msec (%s)\n", nsec/1000./1000., (nsec-offset)/1000./1000., txt);
    //else
    printf("%7.2f msec (%7.2f msec/1M) (%s)\n", nsec/1000./1000., (nsec/(double)BUFSIZE), txt);
    return nsec;
}

#include <math.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    float complex *res_f = malloc(BUFSIZE*sizeof(float complex));
    double complex *res_d = malloc(BUFSIZE*sizeof(double complex));
    struct _vfo vfo = { 0 + I*0, cos(0.001) + I*sin(0.001) };

    double complex *res_testd = malloc(1000*1000*sizeof(double complex));

    printf("\n\nalg3: complex.h phasor rotate, BUFSIZE: %d kB, internal LOOP: %d\n", BUFSIZE/1024, INTERNAL);
    printf("Please tune the BUFSIZE_KB and INTERNAL_2N parameters in the Makefile and recompile this test.\n\n");

    alg3_c(res_testd, &vfo); // wake up! --> CPU from powersave to full tempo

    t_start(); alg3_c(res_d, &vfo); t_end("double - unoptimalized");
    t_start(); alg3_c_f(res_f, &vfo); t_end("float - unoptimalized");
    putchar('\n');

    t_start(); alg3_c_o1(res_d, &vfo); t_end("double - opt1, function parameter struct * --> local variable");
    t_start(); alg3_c_f_o1(res_f, &vfo); t_end("float - opt1, function parameter struct * --> local variable");
    putchar('\n');

    t_start(); alg3_c_o2(res_d, &vfo); t_end("double - opt2, struct * --> static global variable");
    t_start(); alg3_c_f_o2(res_f, &vfo); t_end("float - opt2, struct * --> static global variable");
    putchar('\n');

    t_start(); alg3_c_o3(res_d, &vfo); t_end("double - opt3, static global variable + unrollable INTERNAL loop");
    t_start(); alg3_c_f_o3(res_f, &vfo); t_end("float - opt3, static global variable + unrollable INTERNAL loop");
    putchar('\n');

    t_start(); alg3_c_o4(res_d, &vfo); t_end("double - opt4, built in the unrollable INTERNAL loop (local variable)");
    t_start(); alg3_c_f_o4(res_f, &vfo); t_end("float - opt4, built in the unrollable INTERNAL loop (local variable)");
    putchar('\n');

    t_start(); alg3_c_o5(res_d, &vfo); t_end("double - opt5, built in the unrollable INTERNAL loop (static global variable)");
    t_start(); alg3_c_f_o5(res_f, &vfo); t_end("float - opt5, built in the unrollable INTERNAL loop (static global variable)");
    putchar('\n');

    return 0;
}
