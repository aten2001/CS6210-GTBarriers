//////////////////////////////////
//Deep Datta Roy
//Phil Johnson
//
//Dissemination barrier using OpenMP
//////////////////////////////////
#include "dissemination.h"


//////////////////////////GLOBAL VARIABLES//////////////////////////

#define NO_MESSAGE	0
#define MESSAGE	    1

int numNodes;					//number of threads
int rounds; 					//number of rounds
int j = 0;

/////////////////////////////////////////////////////////////////////


void barrierMPI_init(int barrierThreads){
	numNodes = barrierThreads;				//initialize number of threads for barrier
	rounds = ceil(log(numNodes)/log(2));		//find the number of rounds - log2numNodes
}

void barrierMPI(){
	int i;
	int sendID, recvID;
	int myID;
	int recvMsg;
	int sendMsg = j++;



  	MPI_Comm_rank(MPI_COMM_WORLD, &myID);	//Get ID

	//Do the rounds    
	for (i = 0; i < rounds; i++){
		//Send message to correct thread
		sendID = (myID + (int)pow(2,i))%numNodes;

		MPI_Send(&sendMsg, 1, MPI_INT, sendID, 0, MPI_COMM_WORLD);

		//Recieve Message from correct threads
		recvID = myID -  (int)pow(2,i);
		if (recvID < 0){
			recvID = recvID + numNodes;
		}
		MPI_Recv(&recvMsg, 1, MPI_INT, recvID, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
}
