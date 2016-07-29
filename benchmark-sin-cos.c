#define _GNU_SOURCE
#include <math.h>

#define TLEN (1000*1000)
double sintable1[TLEN];
double costable1[TLEN];

float sintable1_f[TLEN];
float costable1_f[TLEN];

// simple sin() and cos()
void alg1() {
    costable1[0] = 1.;
    sintable1[0] = 0.;
    for (int i=1; i<TLEN; i++) {
	sintable1[i]=sin(2*M_PI*i/TLEN);
	costable1[i]=cos(2*M_PI*i/TLEN);
    }
}

void alg1_f() {
    costable1_f[0] = 1.;
    sintable1_f[0] = 0.;
    for (int i=1; i<TLEN; i++) {
	sintable1_f[i]=sinf(2*(float)M_PI*i/TLEN);
	costable1_f[i]=cosf(2*(float)M_PI*i/TLEN);
    }
}

double sintable2[TLEN];
double costable2[TLEN];

float sintable2_f[TLEN];
float costable2_f[TLEN];

// _GNU_SOURCE --> sincos()
void alg2() {
    costable2[0] = 1.;
    sintable2[0] = 0.;
    for (int i=1; i<TLEN; i++) {
	sincos(2*M_PI*i/TLEN, &sintable2[i], &costable2[i]);
    }
}

void alg2_f() {
    costable2_f[0] = 1.;
    sintable2_f[0] = 0.;
    for (int i=1; i<TLEN; i++) {
	sincosf(2*(float)M_PI*i/TLEN, &sintable2_f[i], &costable2_f[i]);
    }
}


double sintable3[TLEN];
double costable3[TLEN];

// rotating phasor
void alg3() {
    double cosdiff = cos(2*M_PI/TLEN);
    double sindiff = sin(2*M_PI/TLEN);
    costable3[0] = 1;
    sintable3[0] = 0;
    for (int i=1; i<TLEN; i++) {
	costable3[i] = costable3[i-1] * cosdiff - sintable3[i-1] * sindiff;
	sintable3[i] = sintable3[i-1] * cosdiff + costable3[i-1] * sindiff;
    }
}

#include <complex.h>
complex double sincostable3_c[TLEN];

void alg3_c() {
    double complex sincosdiff_c = cos(2*M_PI/TLEN) + sin(2*M_PI/TLEN)*I;
    sincostable3_c[0] = 1 + 0*I;
    for (int i=1; i<TLEN; i++) {
	sincostable3_c[i] = sincostable3_c[i-1] * sincosdiff_c;
    }
}

double test1table_99[TLEN];
double test2table_99[TLEN];

void alg99_copytime() {
    test1table_99[0] = 1.;
    test2table_99[0] = 0.;
    double a=0.1;
    for (int i=1; i<TLEN; i++) {
	test1table_99[i] = a;
	test2table_99[i] = a;
	a+=0.11;
    }
}


#include <time.h>
#include <stdio.h>

unsigned long long timetest(void (*func)(), const char *txt, unsigned long long offset) {
    struct timespec gstart, gend;
    unsigned long long nsec;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
    func();
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);

    nsec = 1000*1000*1000*(gend.tv_sec - gstart.tv_sec) + gend.tv_nsec - gstart.tv_nsec - offset;
    printf("%11.6f msec (%s)\n", nsec/1000./1000., txt);
    return nsec;
}

#include <stdlib.h>
int main(int argc, char **argv) {
    int test;
    unsigned long long offset;
    alg1(); // cpu wake up
    printf("Start with one arg. Value: 0 .. %d\n", TLEN-1);
    offset=timetest(alg99_copytime, "time of data copy", 0);
    timetest(alg1, "double alg1: sin és cos", offset);
    timetest(alg1_f, "float alg1: sinf és cosf", offset);
#ifdef _GNU_SOURCE
    timetest(alg2, "double alg2: sincos()", offset);
    timetest(alg2_f, "float alg2: sincosf()", offset);
#endif
    timetest(alg3, "double alg3: phasor rotate", offset);
    timetest(alg3_c, "double alg3: complex.h phasor rotate", offset);
    if (argc != 2) return -1;
    test = atoi(argv[1]);
    if (test < 0 || test > TLEN-1) return -1;
    printf("\ncos(2*PI*%d/%d) = %f and sin(2*PI*%d/%d) = %f\n", test, TLEN, costable1[test], test, TLEN, sintable1[test]);
    printf("diff alg1f-alg1: %f and %f\n", costable1_f[test] - costable1[test], sintable1_f[test] - sintable1[test]);
#ifdef _GNU_SOURCE
    printf("diff alg2 -alg1: %f and %f\n", costable2[test] - costable1[test], sintable2[test] - sintable1[test]);
    printf("diff alg2f-alg1: %f and %f\n", costable2_f[test] - costable1[test], sintable2_f[test] - sintable1[test]);
#endif
    printf("diff alg3 -alg1: %f and %f\n", costable3[test] - costable1[test], sintable3[test] - sintable1[test]);
    printf("diff alg3c-alg1: %f and %f\n", creal(sincostable3_c[test]) - costable1[test], cimag(sincostable3_c[test]) - sintable1[test]);
}
