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

LDFLAGS=-lm -s
OBJS=benchmark-sin-cos.o

TARGET=benchmark-sin-cos

all: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)