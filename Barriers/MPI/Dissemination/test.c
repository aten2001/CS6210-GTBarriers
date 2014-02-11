#include <stdio.h>
#include <mpi.h>
#include "dissemination.h"

int main(int argc, char **argv)
{
	int my_id, num_processes;

	MPI_Init(&argc, &argv);

  	MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
  	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	barrier_init(num_processes);


  	fprintf(stderr, "0-Hello World from processes %d of %d\n", my_id, num_processes);
	fflush(stderr);
	barrier();
	fflush(stderr);
  	fprintf(stderr, "0-Goodbye World from processes %d of %d\n", my_id, num_processes);
	fflush(stderr);
	barrier();
	fflush(stderr);
  	fprintf(stderr, "1-Hello World from processes %d of %d\n", my_id, num_processes);
	fflush(stderr);


  	MPI_Finalize();
  	return 0;
}

