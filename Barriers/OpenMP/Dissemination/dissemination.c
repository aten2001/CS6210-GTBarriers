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

int numThreads;					//number of threads
int rounds; 					//number of rounds
int** messageArray;			//Array to hold messages

/////////////////////////////////////////////////////////////////////


void barrier_init(int barrierThreads){
	int i;
	
	numThreads = barrierThreads;				//initialize number of threads for barrier
	rounds = ceil(log(numThreads)/log(2));		//find the number of rounds - log2numThreads

	//Inialize message passing array
	messageArray = (int**) malloc(rounds*sizeof(int*));
	for (i = 0; i < rounds; i++){
		messageArray[i] = (int*) calloc(numThreads, sizeof(int));
	}
}

void barrier(){
	int i;
	int sendID;
	int myID = omp_get_thread_num();

	//Do the rounds
	for (i = 0; i < rounds; i++){
		sendID = (myID + (int)pow(2,i))%numThreads;			//Figure out who to send message
		messageArray[i][sendID] = MESSAGE;				//send message
		//if haven;t recieved message yet, loop
		while(messageArray[i][myID] == NO_MESSAGE);
	}
}
