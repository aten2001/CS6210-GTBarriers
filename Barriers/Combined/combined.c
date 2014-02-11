//////////////////////////////////
//Deep Datta Roy
//Phil Johnson
//
//Dissemination/MCS barrier using OpenMP/MPI
//////////////////////////////////
#include "combined.h"

//////////////////////////GLOBAL VARIABLES//////////////////////////

#define TRUE			1
#define FALSE		    0

int SENSE = FALSE;

/////////////////////////////////////////////////////////////////////

void barrier_init(int nodes, int threads){
	barrierMPI_init(nodes);
	barrierOpenMP_init(threads);
}

void barrier(){
    int threadNum = omp_get_thread_num();
	int flag = SENSE; 

	barrierOpenMP();

	//only first thread does mpi barrier
	if (threadNum==0){
		barrierMPI();
		//Switch sense variable		
		if (flag == FALSE){
			SENSE = TRUE;
		}else{
			SENSE = FALSE;
		}
	} else{
		//Wait for thread 1 to finish
		while(flag == SENSE);
	}
}
