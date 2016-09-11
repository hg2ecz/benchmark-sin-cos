#include "benchmark-rotate-algs.h"

void alg3_c(double complex *out, struct _vfo *vfo) {
    int i;
    for (i=0; i<BUFSIZE; i++) {
	vfo->state *= vfo->delta;
	out[i] = vfo->state;
    }
}

void alg3_c_f(float complex *out, struct _vfo *vfo) {
    int i;
    for (i=0; i<BUFSIZE; i++) {
	vfo->state *= vfo->delta;
	out[i] = vfo->state;
    }
}


void alg3_c_o1(double complex *out, struct _vfo *vfo_in) {
    int i;
    struct _vfo vfo = *vfo_in; // local shadow copy
    for (i=0; i<BUFSIZE; i++) {
	vfo.state *= vfo.delta;
	out[i] = vfo.state;
    }
    vfo_in->state = vfo.state; // from local back to global
}

void alg3_c_f_o1(float complex *out, struct _vfo *vfo_in) {
    int i;
    struct _vfo vfo = *vfo_in; // local shadow copy
    for (i=0; i<BUFSIZE; i++) {
	vfo.state *= vfo.delta;
	out[i] = vfo.state;
    }
    vfo_in->state = vfo.state; // from local back to global
}


static struct _vfo st_vfo;
void alg3_c_o2(double complex *out, struct _vfo *vfo_in) {
    int i;
    st_vfo = *vfo_in;              // static variable shadow copy
    for (i=0; i<BUFSIZE; i++) {
	st_vfo.state *= st_vfo.delta;
	out[i] = st_vfo.state;
    }
    vfo_in->state = st_vfo.state;  // from static back to global
}

void alg3_c_f_o2(float complex *out, struct _vfo *vfo_in) {
    int i;
    st_vfo = *vfo_in;              // static variable shadow copy
    for (i=0; i<BUFSIZE; i++) {
	st_vfo.state *= st_vfo.delta;
	out[i] = st_vfo.state;
    }
    vfo_in->state = st_vfo.state;  // from static back to global
}

// more optimalization --> UNROLL
static void alg3_c_o3_inline(double complex *out) {
    int j;
    for (j=0; j<INTERNAL; j++) {
	st_vfo.state *= st_vfo.delta;
	out[j] = st_vfo.state;
    }
}
void alg3_c_o3(double complex *out, struct _vfo *vfo_in) {
    int i;
    st_vfo = *vfo_in;              // static variable shadow copy
    for (i=0; i<BUFSIZE; i+=INTERNAL) {
	alg3_c_o3_inline(&out[i]);
    }
    vfo_in->state = st_vfo.state;  // from static back to global
}

static void alg3_c_f_o3_inline(float complex *out) {
    int j;
    for (j=0; j<INTERNAL; j++) {
	st_vfo.state *= st_vfo.delta;
	out[j] = st_vfo.state;
    }
}
void alg3_c_f_o3(float complex *out, struct _vfo *vfo_in) {
    int i;
    st_vfo = *vfo_in;               // static variable shadow copy
    for (i=0; i<BUFSIZE; i+=INTERNAL) {
	alg3_c_f_o3_inline(&out[i]);
    }
    vfo_in->state = st_vfo.state;   // from static back to global
}




// inline func build into for loop -- local variable
void alg3_c_o4(double complex *out, struct _vfo *vfo_in) {
    int i;
    struct _vfo vfo = *vfo_in;   // local shadow copy
    for (i=0; i<BUFSIZE; i+=INTERNAL) {
	int j;
	double complex *o = &out[i];
	for (j=0; j<INTERNAL; j++) {
	    vfo.state *= vfo.delta;
	    o[j] = vfo.state;    // from local back to global
	}
    }
    vfo_in->state = vfo.state;
}

void alg3_c_f_o4(float complex *out, struct _vfo *vfo_in) {
    int i;
    struct _vfo vfo = *vfo_in;    // local shadow copy
    for (i=0; i<BUFSIZE; i+=INTERNAL) {
	int j;
	float complex *o = &out[i];
	for (j=0; j<INTERNAL; j++) {
	    vfo.state *= vfo.delta;
	    o[j] = vfo.state;
	}
    }
    vfo_in->state = vfo.state;    // from local back to global

}

// inline func build into for loop -- static variable
void alg3_c_o5(double complex *out, struct _vfo *vfo_in) {
    int i;
    st_vfo = *vfo_in;              // static shadow copy
    for (i=0; i<BUFSIZE; i+=INTERNAL) {
	int j;
	double complex *o = &out[i];
	for (j=0; j<INTERNAL; j++) {
	    st_vfo.state *= st_vfo.delta;
	    o[j] = st_vfo.state;
	}
    }
    vfo_in->state = st_vfo.state;  // from static back to global
}

void alg3_c_f_o5(float complex *out, struct _vfo *vfo_in) {
    int i;
    st_vfo = *vfo_in;              // static shadow copy
    for (i=0; i<BUFSIZE; i+=INTERNAL) {
	int j;
	float complex *o = &out[i];
	for (j=0; j<INTERNAL; j++) {
	    st_vfo.state *= st_vfo.delta;
	    o[j] = st_vfo.state;
	}
    }
    vfo_in->state = st_vfo.state;  // from static back to global
}
