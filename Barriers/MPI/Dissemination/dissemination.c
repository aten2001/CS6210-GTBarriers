//////////////////////////////////
//Deep Datta Roy
//Phil Johnson
//
//Dissemination barrier using OpenMP
//////////////////////////////////
#include "dissemination.h"
#include <sys/time.h>

//////////////////////////GLOBAL VARIABLES//////////////////////////

#define NO_MESSAGE	0
#define MESSAGE	    1

int numThreads;					//number of threads
int rounds; 					//number of rounds
int j = 0;

/////////////////////////////////////////////////////////////////////


void barrier_init(int barrierThreads){
	numThreads = barrierThreads;				//initialize number of threads for barrier
	rounds = ceil(log(numThreads)/log(2));		//find the number of rounds - log2numThreads
}

void barrier(){
	int i;
	int sendID, recvID;
	int myID;
	int recvMsg;
	int sendMsg = j++;
	struct timeval tv;

  	MPI_Comm_rank(MPI_COMM_WORLD, &myID);	//Get ID
//////////////////////////////////////
gettimeofday(&tv,NULL);
sendMsg = tv.tv_usec;
fprintf(stderr, "Start Time:%d - %d\n", sendMsg, myID);
//////////////////////////////////////
	//Do the rounds    
	for (i = 0; i < rounds; i++){
		//Send message to correct thread
		sendID = (myID + (int)pow(2,i))%numThreads;
		
		gettimeofday(&tv,NULL);
		sendMsg = tv.tv_usec;
		MPI_Send(&sendMsg, 1, MPI_INT, sendID, 0, MPI_COMM_WORLD);
		//fprintf(stderr, "Sent:%d from %d to %d\n", sendMsg, myID, sendID);
		//Recieve Message from correct threads
		recvID = myID -  (int)pow(2,i);
		if (recvID < 0){
			recvID = recvID + numThreads;
		}
		MPI_Recv(&recvMsg, 1, MPI_INT, recvID, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		//fprintf(stderr, "Recv:%d from %d to %d\n", recvMsg, recvID, myID);
	}
//////////////////////////////////////
gettimeofday(&tv,NULL);
sendMsg = tv.tv_usec;
fprintf(stderr, "Leave Time:%d - %d\n", sendMsg, myID);
//////////////////////////////////////
}
