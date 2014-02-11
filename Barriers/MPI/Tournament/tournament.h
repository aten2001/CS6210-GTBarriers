//////////////////////////////////
//Deep Datta Roy
//Phil Johnson
//
//Dissemination barrier using MPI
//////////////////////////////////
#ifndef _TOURNAMENT

#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <mpi.h>

//////////////////////////FUNCTION PROTOTYPES//////////////////////////

//////////////////////////////////
//barrier_init()
//
//parameters: 
//	int barrierThreads - # threads
//
//return:
//	none
//////////////////////////////////
void barrier_init(int barrierThreads);

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
