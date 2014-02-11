OMPFLAGS = -fopenmp
OMPLIBS = -lgomp -lm

CC = gcc
CPPFLAGS = -g -Wall  $(OMPFLAGS)
LDFLAGS = -g -Wall
LDLIBS = $(OMPLIBS)

MPICC = mpicc
MPICH = /usr/lib64/openmpi/1.4-gcc
CFLAGS = -I$(MPICH)/include

all: test

test: test.o dissemination.o mcs.o combined.o
	$(MPICC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

clean:
	rm -f *.o test
