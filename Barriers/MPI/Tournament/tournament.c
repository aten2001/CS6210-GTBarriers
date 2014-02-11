//////////////////////////////////
//Deep Datta Roy
//Phil Johnson
//
//Dissemination barrier using OpenMP
//////////////////////////////////
#include "tournament.h"


//////////////////////////GLOBAL VARIABLES//////////////////////////

#define NO_MESSAGE	0
#define MESSAGE	    1

int numThreads;					//number of threads
int rounds; 					//number of rounds

/////////////////////////////////////////////////////////////////////


void barrier_init(int barrierThreads){
	numThreads = barrierThreads;				//initialize number of threads for barrier
	rounds = ceil(log(numThreads)/log(2));		//find the number of rounds - log2numThreads
}

void barrier(){
	int sendID, recvID;
	int myID;
	int recvMsg;
	int sendMsg = MESSAGE;
	int roundFactor = 2;

  	MPI_Comm_rank(MPI_COMM_WORLD, &myID);	//Get ID
	
	//check if supposed to be a winner
	while ((myID%roundFactor)==0){

		//Check if who you are supposed to recieve from exists
		recvID = myID + roundFactor/2;

		//Do a blocking recieve if it exists
		if (recvID<numThreads){		
			MPI_Recv(&recvMsg, 1, MPI_INT, recvID, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}else{
			roundFactor=roundFactor*2;
			break;		
		}

		//Change round factor so winner is different
		roundFactor=roundFactor*2;

	}

	//Send notification to right thread
	if (myID!=0){
		sendID = myID - roundFactor/2;		  	
		MPI_Send(&sendMsg, 1, MPI_INT, sendID, 0, MPI_COMM_WORLD);
	}

	//Wait to recieve wake up
	if (myID!=0){
		MPI_Recv(&recvMsg, 1, MPI_INT, sendID, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	//Wake up threads who lost to you
	while (roundFactor!=1){
		//find who to send to
		sendID = myID + roundFactor/2;

		//Check if suposed to send to non existent
		if (sendID>=numThreads){
			roundFactor=roundFactor/2;
			continue;
		}	

		//check if supposed to send
		if (myID%roundFactor!=0){
			roundFactor=roundFactor/2;
			continue;
		}

		//Send
		MPI_Send(&sendMsg, 1, MPI_INT, sendID, 0, MPI_COMM_WORLD);

		//Change round factor so winner is different
		roundFactor=roundFactor/2;
	}
}
