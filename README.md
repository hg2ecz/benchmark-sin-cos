Fill sin and cos table 1 000 000 elements with different method. Printed result: algtime (algtime-copytime)
<pre>
Benchmark result for RaspberryPi3 (1.2 GHz ARM Cortex A53 @32 bit OS), gcc-5.4 (Debian-9 testing):

  18.62 msec (double time of data copy)
   9.35 msec (float time of data copy)

 254.82 ( 236.20) msec (double alg1: sin és cos)
 271.02 ( 252.40) msec (double alg2: sincos())
  26.18 (   7.56) msec (double alg3: phasor rotate)
  25.43 (   6.81) msec (double alg3: complex.h phasor rotate)

 199.88 ( 190.53) msec (float alg1: sinf és cosf)
 199.88 ( 190.54) msec (float alg2: sincosf())
  22.37 (  13.02) msec (float alg3: phasor rotate)
  19.04 (   9.69) msec (float alg3: complex.h phasor rotate)

Benchmark result for Odroid-C1 (1.5 GHz ARM Cortex A5), gcc-5.4 (Ubuntu 16.04.1):

  32.11 msec (double time of data copy)
  15.29 msec (float time of data copy)

 313.32 ( 281.21) msec (double alg1: sin és cos)
 333.73 ( 301.62) msec (double alg2: sincos())
  32.32 (   0.21) msec (double alg3: phasor rotate)
  32.39 (   0.28) msec (double alg3: complex.h phasor rotate)

 182.55 ( 167.26) msec (float alg1: sinf és cosf)
 182.29 ( 166.99) msec (float alg2: sincosf())
  23.14 (   7.85) msec (float alg3: phasor rotate)
  21.85 (   6.56) msec (float alg3: complex.h phasor rotate)

Benchmark result for Intel J1900 (2.0 GHz Silvermont architecture), gcc-5.4 (Debian-9 testing):

  10.60 msec (double time of data copy)
   5.31 msec (float time of data copy)

 132.20 ( 121.60) msec (double alg1: sin és cos)
 142.18 ( 131.58) msec (double alg2: sincos())
  15.54 (   4.94) msec (double alg3: phasor rotate)
  15.61 (   5.02) msec (double alg3: complex.h phasor rotate)

  58.84 (  53.53) msec (float alg1: sinf és cosf)
  58.37 (  53.06) msec (float alg2: sincosf())
  11.58 (   6.27) msec (float alg3: phasor rotate)
  11.15 (   5.84) msec (float alg3: complex.h phasor rotate)

</pre>
