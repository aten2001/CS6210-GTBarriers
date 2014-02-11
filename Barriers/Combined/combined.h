//////////////////////////////////
//Deep Datta Roy
//Phil Johnson
//
//MCS barrier using OpenMP
//////////////////////////////////
#ifndef _COMBINED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <mpi.h>
#include <mpi.h>
#include <omp.h>
#include "dissemination.h"
#include "mcs.h"


//////////////////////////////////
//barrier_init()
//
//parameters: 
//	int nodes - # nodes
//	int threads - # threads
//
//return:
//	none
//////////////////////////////////
void barrier_init(int nodes, int threads);

//////////////////////////////////
//barrier()
//
//parameters: 
//	none
//
//return:
//	none
//////////////////////////////////
void barrier();

#endif
