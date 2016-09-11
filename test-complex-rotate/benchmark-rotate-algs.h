#include <complex.h>

#define BUFSIZE (BUFSIZE_KB*1024)
#define INTERNAL (1<<INTERNAL_2N)

struct _vfo {
    double complex state;
    double complex delta;
};

void alg3_c(double complex *out, struct _vfo *vfo);
void alg3_c_f(float complex *out, struct _vfo *vfo);

void alg3_c_o1(double complex *out, struct _vfo *vfo);
void alg3_c_f_o1(float complex *out, struct _vfo *vfo);

void alg3_c_o2(double complex *out, struct _vfo *vfo);
void alg3_c_f_o2(float complex *out, struct _vfo *vfo);

void alg3_c_o3(double complex *out, struct _vfo *vfo);
void alg3_c_f_o3(float complex *out, struct _vfo *vfo);

void alg3_c_o4(double complex *out, struct _vfo *vfo);
void alg3_c_f_o4(float complex *out, struct _vfo *vfo);

void alg3_c_o5(double complex *out, struct _vfo *vfo);
void alg3_c_f_o5(float complex *out, struct _vfo *vfo);

