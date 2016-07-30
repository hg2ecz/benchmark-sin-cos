#define _GNU_SOURCE
#include <math.h>

#define TLEN (1000*1000)

// test0 - copy a number ... measure time of copy
double test1table_99[TLEN];
double test2table_99[TLEN];

float test1table_99_f[TLEN];
float test2table_99_f[TLEN];

void alg99_copytime() {
    int i;
    test1table_99[0] = 0.1;
    test2table_99[0] = 0.1;
    for (i=1; i<TLEN; i++) {
	test1table_99[i] = 0.1;
	test2table_99[i] = 0.1;
    }
}

void alg99_copytime_float() {
    int i;
    test1table_99_f[0] = 0.1;
    test2table_99_f[0] = 0.1;
    for (i=1; i<TLEN; i++) {
	test1table_99_f[i] = 0.1;
	test2table_99_f[i] = 0.1;
    }
}

// simple cos() and sin() ... and float
double sintable1[TLEN];
double costable1[TLEN];

float sintable1_f[TLEN];
float costable1_f[TLEN];

void alg1() {
    int i;
    costable1[0] = 1.;
    sintable1[0] = 0.;
    for (i=1; i<TLEN; i++) {
	sintable1[i]=sin(2*M_PI*i/TLEN);
	costable1[i]=cos(2*M_PI*i/TLEN);
    }
}

void alg1_f() {
    int i;
    costable1_f[0] = 1.;
    sintable1_f[0] = 0.;
    for (i=1; i<TLEN; i++) {
	sintable1_f[i]=sinf(2*(float)M_PI*i/TLEN);
	costable1_f[i]=cosf(2*(float)M_PI*i/TLEN);
    }
}

// _GNU_SOURCE --> sincos() ... and float
double sintable2[TLEN];
double costable2[TLEN];

float sintable2_f[TLEN];
float costable2_f[TLEN];

void alg2() {
    int i;
    costable2[0] = 1.;
    sintable2[0] = 0.;
    for (i=1; i<TLEN; i++) {
	sincos(2*M_PI*i/TLEN, &sintable2[i], &costable2[i]);
    }
}

void alg2_f() {
    int i;
    costable2_f[0] = 1.;
    sintable2_f[0] = 0.;
    for (i=1; i<TLEN; i++) {
	sincosf(2*(float)M_PI*i/TLEN, &sintable2_f[i], &costable2_f[i]);
    }
}


// rotating phasor ... alg double, resultvector double and float
double sintable3[TLEN];
double costable3[TLEN];

float sintable3_f[TLEN];
float costable3_f[TLEN];

void alg3() {
    int i;
    double cosdiff = cos(2*M_PI/TLEN);
    double sindiff = sin(2*M_PI/TLEN);
    double cosval = 1.;
    double sinval = 0.;
    double cosval_new;
    costable3[0] = cosval;
    sintable3[0] = sinval;
    for (i=1; i<TLEN; i++) {
	cosval_new = cosval * cosdiff - sinval * sindiff;
	sinval = sinval * cosdiff + cosval * sindiff;
	cosval = cosval_new;
	costable3[i] = cosval;
	sintable3[i] = sinval;
    }
}

void alg3_f() {
    int i;
    double cosdiff = cos(2*M_PI/TLEN);
    double sindiff = sin(2*M_PI/TLEN);
    double cosval = 1.; // double, else accumulation error
    double sinval = 0.; // double, else accumulation error
    double cosval_new;
    costable3_f[0] = cosval;
    sintable3_f[0] = sinval;
    for (i=1; i<TLEN; i++) {
	cosval_new = cosval * cosdiff - sinval * sindiff;
	sinval = sinval * cosdiff + cosval * sindiff;
	cosval = cosval_new;
	costable3_f[i] = cosval;
	sintable3_f[i] = sinval;
    }
}

// rotating phasor2 - with complex.h ... alg double, resultvector double and float
#include <complex.h>
complex double sincostable3_c[TLEN];
complex float  sincostable3_c_f[TLEN];

void alg3_c() {
    int i;
    double complex sincosdiff_c = cos(2*M_PI/TLEN) + sin(2*M_PI/TLEN)*I;
    double complex sincosval = 1. + 0.*I;
    sincostable3_c[0] = sincosval;
    for (i=1; i<TLEN; i++) {
	sincosval *= sincosdiff_c;
	sincostable3_c[i] = sincosval;
    }
}

void alg3_c_f() {
    int i;
    double complex sincosdiff_c = cos(2*M_PI/TLEN) + sin(2*M_PI/TLEN)*I;
    double complex sincosval = 1. + 0.*I; // double, else accumulation error
    sincostable3_c[0] = sincosval;
    for (i=1; i<TLEN; i++) {
	sincosval *= sincosdiff_c;
	sincostable3_c_f[i] = sincosval;
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

    nsec = 1000*1000*1000*(gend.tv_sec - gstart.tv_sec) + gend.tv_nsec - gstart.tv_nsec;
    if (offset > 0) printf("%7.2f (%7.2f) msec (%s)\n", nsec/1000./1000., (nsec-offset)/1000./1000., txt);
    else printf("%7.2f msec (%s)\n", nsec/1000./1000., txt);
    return nsec;
}

#include <stdlib.h>
int main(int argc, char **argv) {
    int test;
    unsigned long long offset, offset_f;
    alg1(); // cpu wake up
    printf("Start with one arg. Value: 0 .. %d\n\n", TLEN-1);
    printf("Fill sin and cos table %d elements with different method. Printed result: algtime (algtime-copytime)\n", TLEN);
    offset=timetest(alg99_copytime, "double time of data copy", 0);
    offset_f=timetest(alg99_copytime_float, "float time of data copy", 0);
    printf("\n");
    timetest(alg1, "double alg1: sin és cos", offset);
    timetest(alg2, "double alg2: sincos()", offset);
    timetest(alg3, "double alg3: phasor rotate", offset);
    timetest(alg3_c, "double alg3: complex.h phasor rotate", offset);
    printf("\n");
    timetest(alg1_f, "float alg1: sinf és cosf", offset_f);
    timetest(alg2_f, "float alg2: sincosf()", offset_f);
    timetest(alg3_f, "float alg3: phasor rotate", offset_f);
    timetest(alg3_c_f, "float alg3: complex.h phasor rotate", offset_f);

    if (argc != 2) return -1;
    test = atoi(argv[1]);
    if (test < 0 || test > TLEN-1) return -1;
    printf("\ncos(2*PI*%d/%d) = %f and sin(2*PI*%d/%d) = %f\n", test, TLEN, costable1[test], test, TLEN, sintable1[test]);
    printf("diff alg2 -alg1: %f and %f\n", costable2[test] - costable1[test], sintable2[test] - sintable1[test]);
    printf("diff alg3 -alg1: %f and %f\n", costable3[test] - costable1[test], sintable3[test] - sintable1[test]);
    printf("diff alg3c-alg1: %f and %f\n", creal(sincostable3_c[test]) - costable1[test], cimag(sincostable3_c[test]) - sintable1[test]);

    printf("\ndiff alg1f-alg1: %f and %f\n", costable1_f[test] - costable1[test], sintable1_f[test] - sintable1[test]);
    printf("diff alg2f-alg1: %f and %f\n", costable2_f[test] - costable1[test], sintable2_f[test] - sintable1[test]);
    printf("diff alg3f -alg1: %f and %f\n", costable3_f[test] - costable1[test], sintable3_f[test] - sintable1[test]);
    printf("diff alg3cf-alg1: %f and %f\n", creal(sincostable3_c_f[test]) - costable1[test], cimag(sincostable3_c_f[test]) - sintable1[test]);

    return 0;
}
