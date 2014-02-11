#include <stdio.h>
#include "combined.h"
#include <mpi.h>
#include <omp.h>

#define NUM_THREADS 10

int main(int argc, char **argv)
{
	int my_id, num_processes;

	//INitialize MPI
	MPI_Init(&argc, &argv);
  	MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
  	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

	omp_set_num_threads(NUM_THREADS);

	barrier_init(num_processes, NUM_THREADS);

#pragma omp parallel
  {
    // Now we're in the parallel section
    int num_threads = omp_get_num_threads();
    int thread_num = omp_get_thread_num();

    printf("Hello World from thread %d -%d.\n", my_id, thread_num);
	barrier();
    printf("Goodbye World from thread %d - %d.\n", my_id, thread_num);
	barrier();
    printf("Hello World from thread %d -%d.\n", my_id, thread_num);
  } // implied barrier

  	MPI_Finalize();
  	return 0;
}

