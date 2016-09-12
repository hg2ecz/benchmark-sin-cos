CC=gcc
CFLAGS=-Wall -Ofast -funroll-loops -fopt-info

CFLAGS+=-mcpu=cortex-a5 -mfpu=neon-fp16
#CFLAGS+=-mcpu=cortex-a7 -mfpu=neon-vfpv4
#CFLAGS+=-mcpu=cortex-a8 -mfpu=neon
#CFLAGS+=-mcpu=cortex-a9 -mfpu=neon-fp16
#CFLAGS+=-mcpu=cortex-a15 -mfpu=neon-vfpv4
#CFLAGS+=-mcpu=cortex-a53 -mfpu=neon-fp-armv8

#CFLAGS+=-std=gnu90
#CFLAGS+=-std=c99

# BUFSIZE --> larger is better, limit: memory
# INTERNAL_2N --> 2^N internal loop (4 ==> 2^4 = 16)
CFLAGS+=-DBUFSIZE_KB=10000 -DINTERNAL_2N=4

LDFLAGS=-lm -s
OBJS=benchmark-rotate-algs.o benchmark-rotate.o

TARGET=benchmark-rotate

all: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)