//////////////////////////////////
//Deep Datta Roy
//Phil Johnson
//
//MCS barrier using OpenMP
//////////////////////////////////
#include "mcs.h"

//////////////////////////GLOBAL VARIABLES//////////////////////////

#define NO_CHILD	-1
#define NOT_READY	0
#define READY	    1

int numThreads;					//number of threads
treeNode* nodeArray;			//Array to hold messages

/////////////////////////////////////////////////////////////////////


void barrierOpenMP_init(int barrierThreads){
	int i, j, id;
	
	numThreads = barrierThreads;				//initialize number of threads for barrier
	nodeArray = (treeNode*) malloc(numThreads*sizeof(treeNode));	//Allocate tree

	//Organize Tree
	for (i = 0; i < numThreads; i++){

		if (i==0){
			nodeArray[i].parent = -1;				//Root node has no parents
			nodeArray[i].wake = READY;				//Intialize wake to 1 for parent
		}else{

			nodeArray[i].parent =  (i-1)/4;			//Set Parent
			nodeArray[i].wake = 0;			//Intialize wake to 0
		}	

		//Set up pointers for releasing barrier
		for (j = 1; j <= 2 ;j++){
			id = 2*i+j;					//id of child

			///Check if child exists and put it accordingly into children list
			if (id < numThreads){
				nodeArray[i].childrenDown[j-1] = id;
			}else{
				nodeArray[i].childrenDown[j-1] = NO_CHILD;
			}
		}		

		//Set up pointers for setting barrier
		for (j = 1; j <= 4 ;j++){
			id = 4*i+j;					//id of child

			///Check if child exists and put it accordingly into children list
			if (id < numThreads){
				nodeArray[i].childrenUp[j-1] = id;
				nodeArray[i].childrenReady[j-1] = NOT_READY;
			}else{
				nodeArray[i].childrenUp[j-1] = NO_CHILD;
				nodeArray[i].childrenReady[j-1] = READY;
			}
		}		
		


	}
}

void barrierOpenMP(){
	int i;
	int childrenFlag;
	int myID = omp_get_thread_num();

	childrenFlag = NOT_READY;		//Flag for if children arrived

	//Wait for all children	
	while(childrenFlag == NOT_READY){
		//Check if all children ready	
		for (i = 0; i < 4 ;i++){
			//Check if child is ready
			if (nodeArray[myID].childrenReady[i]!=READY){
				break;
			}
			
			//if all children ready, mark it
			if (i==3){
				childrenFlag = READY;

				//Reset flags for ready
				for (i = 0; i < 4 ;i++){
					if (nodeArray[myID].childrenUp[i]!=NO_CHILD){
						nodeArray[myID].childrenReady[i]=NOT_READY;
					}
				}

			}
		}
	}



	//set ready in parent
	if (nodeArray[myID].parent!=-1){
		nodeArray[nodeArray[myID].parent].childrenReady[(myID-1)%4] = READY;
	}		

	//Spin while wait for barrier release
	while(nodeArray[myID].wake==NOT_READY);					
	//Reset wake flag
	if (nodeArray[myID].parent!=-1){
		nodeArray[myID].wake=NOT_READY;
	}

	//Alert children that ready to release barrier
	for (i = 0; i < 2 ;i++){
		if (nodeArray[myID].childrenDown[i]!=NO_CHILD){
			nodeArray[nodeArray[myID].childrenDown[i]].wake = READY;
		}
	}



}
