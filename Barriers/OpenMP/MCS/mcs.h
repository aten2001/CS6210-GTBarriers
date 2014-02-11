//////////////////////////////////
//Deep Datta Roy
//Phil Johnson
//
//MCS barrier using OpenMP
//////////////////////////////////
#ifndef _MCS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <omp.h>

//////////////////////////STRUCTURES//////////////////////////
typedef struct _treeNode{
	int parent;

	//Associated with return down tree
	int childrenDown[2];				//list of children
	int wake;						//wake up

	//Associated with going up tree
	int childrenUp[4];				//list of children
	int childrenReady[4];			//ready or not
}treeNode;

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
