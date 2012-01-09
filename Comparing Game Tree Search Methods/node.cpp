//Author: John Kilfeather
#include "node.h"

GameNode::GameNode()//root node initializer
{
	//set static and true values to random integer in the range [-100, 100]
	trueValue = -100 + rand()%201;
	staticValue = -100 + rand()%201;
	//set maximum number of daughters to a random integer between minimum and maximum branching factors
	maxDaughters = branchingMin + (rand() % (branchingMax + 1 - branchingMin));

	daughters = new GameNode* [maxDaughters];
	initializedDaughters = 0;
	//set best daughter location:
	//1. bestDaughter is automatically set as first daughter with probability = orderingQuality
	//2. the rest of the time its position is selected randomly amongst all the daughter nodes (including the first node)
	if(maxDaughters > 0)	{

		if(((double)rand()/(double)RAND_MAX) <= orderingQuality)
			bestDaughter = 0;
		else
			bestDaughter = rand()%maxDaughters;
	}
}

//Daughter node initialiser - initialised in steps:
//1. set true value (dependent on parents true value and if it's the "best" node)
//2. set static value (dependent on true value)
//3. set number of children (dependent on true value), create pointers to these children and set initialized children to 0
//4. set "best" child location (dependent on number of children)
GameNode::GameNode(int parentTrue, int height, bool isBest)
{
	//1. Set True Value
	//if node is best node set its true value to negation of parent's true value
	//otherwise set it to some value x, where -parentTrue < x <= WIN
	if(isBest)
		trueValue = - parentTrue;
	else
		trueValue = - parentTrue + 1 + (rand() % (WIN + parentTrue));

	//2. Set Static Value
	//if not win or loss or leaf node, set static value to some value within the range trueValue-50 to trueValue+50
	if(trueValue != WIN && trueValue != LOSE && height!= 0)
	{
		//ensure WIN and LOSE values not reached or exceeded
		int minVal = max(LOSE+1, trueValue-50);
		int maxVal = min(WIN-1, trueValue+50);
		staticValue =  minVal + rand()%(maxVal + 1 - minVal);
	}
	else
		staticValue = trueValue;

	//3. Set number of daughter nodes
	//if win or loss position no daughters
	//otherwise a random number of daughters between min and max branching factors
	if(trueValue == WIN || trueValue == LOSE)
		maxDaughters = 0;
	else
		maxDaughters = branchingMin + (rand() % (branchingMax + 1 - branchingMin)); 

	daughters = new GameNode* [maxDaughters];
	initializedDaughters = 0;

	//4. Set Best Daughter location
	//i. bestDaughter is automatically set as first daughter with probability = orderingQuality
	//ii. the rest of the time its position is selected randomly amongst all the daughter nodes (including the first node)
	if(maxDaughters > 0)	{
		if(((double)rand()/(double)RAND_MAX) <= orderingQuality)
			bestDaughter = 0;
		else
			bestDaughter = rand() % maxDaughters;
	}
}

GameNode::~GameNode(){
	//delete daughters
	for(int i = 0; i<initializedDaughters; i++)
		delete daughters[i];
	//delete array of pointers to daughters
	delete daughters;
}

//height must be passed to this function to determine if node is at depth limit or not
//as node will be initialised differently if it is (static value will = true value)
GameNode* GameNode::retrieveDaughter(int i, int height)
{
	if(i >= maxDaughters)//return null pointer if non-existant daughter is requested
		return 0;
	else{
		//if not yet initialized create node before returning - this test assumes daughters will be intialized in numerical order 
		//if out of sequence initialisation was required could replace integer initializedDaughters with an array of booleans 
		if(i>= initializedDaughters){
			//test if daughter to be initialised will be the "best" daughter
			bool best = false;
			if(i == bestDaughter)
				best = true;
			
			//initialize daughter
			daughters[i] = new GameNode(trueValue, height, best);
			initializedDaughters++;
		}
		//return pointer to node
		return daughters[i];		
	}
}


int GameNode::getMaxDaughters()
{ return maxDaughters; }

int GameNode::getStaticValue()
{ return staticValue; }

//reorders game nodes according to the values in array newOrder
//eg. if neworder was {2,0,1} the 2nd daughter would be moved to the 0th index etc.
void GameNode::reorderNodes(int newOrder[], int numNodes)
{
	//create copy of daughters pointers
	GameNode* temp[maxDaughters];
	for(int i = 0; i < maxDaughters; i++)
		temp[i] = daughters[i];
	//reassign daughter pointers to new order
	for(int i = 0; i<numNodes; i++)
		daughters[i] = temp[newOrder[i]];
}

void GameNode::print()
{
	cout<<"Static: "<<staticValue<<", True:"<<trueValue<<", Daughters: "<<maxDaughters;
}
