/*main.cpp
Author: John Kilfeather
Program to compare the following tree search methods:
1.Negamax Alpha Beta Search (NABS)
2.Principal Variation Search in an iterative deepening framework (PVS)
3.PVS with node reordering after each iteration
Uses a simulated game tree class to perform tests, and in order to keep
the same tree for each search nodes are not deleted once searched
*/

#include<iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <algorithm>
#include"node.h"

using namespace std;

//struct used to store node details when reordering nodes
struct nodeDetails{
	int index;
	int value;
};

//NABS tree search
int negamaxAlphaBeta(GameNode* currentNode, int height, int alpha, int beta, 
                     int& staticEvalCount, bool printing = false);
//pvs tree search
int pvs(GameNode* currentNode, int height, int alpha, int beta, int& staticEvalCount,
        bool reOrd = false);
//iterative deepening function - embeds pvs search in iterative deepening framework
int iterativeDeepening(GameNode* currentNode, int maxHeight, int& staticEvalCount,
                       bool reOrd = false);
//function to sort an array of nodeDetails by value and return the indices of
//each node to ouput array
void sortNodes(nodeDetails inputArray[], int outputArray[], int arraySize);
//prints the specified number of tabs
void printTabs(int numTabs);

//static variables
int GameNode::branchingMin = 0;
int GameNode::branchingMax = 0;
double GameNode::orderingQuality = 0.0;


int main(int argc, char* argv[])
{
	int startHeight = 0;

  // initialize random seed
  srand ( time(NULL) );

	//retrieve parameters checking they are within range
	//argv[0] = GameNode::branchingMin
	//argv[1] = GameNode::branchingMax
	//argv[2] = startHeight
	//argv[3] = GameNode::orderingQuality
	if(argc <= 4){
		cout<<endl
				<<"Incorrect number of arugments supplied"
				<<" - correct way to call the program is as follows:"
				<<endl<<endl
		    <<"assignment1 bMin bMax height quality"<<endl<<endl
		    <<"where:"<<endl
				<<"\tbMin is a positive integer representing"
				<<" the minimum number of daughter nodes for each (non-leaf) node"
				<<endl
		    <<"\tbMax is an integer >= bMin, representing"
				<<" the maximum number of daughter nodes for each (non-leaf) node"
				<<endl
		    <<"\theight is a positive integer representing"
				<<" the depth to which the tree is to be searched"<<endl
		    <<"\tquality is a real number in the range [0,1] representing"
				<<" the probability that the first daughter of"
				<<endl
		    <<"\teach node will be automatically chosen to be the best one"
				<<" rather than chosen randomly"<<endl<<endl;    
		return 1;
	}
	else
	{
		GameNode::branchingMin = atoi(argv[1]);
		if(GameNode::branchingMin < 0){
			cout<<"error min branching factor ("<<GameNode::branchingMin<<") should be >= 0"<<endl;
			return 1;
		}

		GameNode::branchingMax = atoi(argv[2]);
		if(GameNode::branchingMax < GameNode::branchingMin){
			cout<<"error max branching factor ("<<GameNode::branchingMax
			    <<") should be >= min branching factor ("<<GameNode::branchingMin<<")"<<endl;
			return 1;
		}

		startHeight = atoi(argv[3]);
		if(startHeight < 0){
			cout<<"error height ("<<startHeight<<") should be >= 0"<<endl;
			return 1;
		}

		GameNode::orderingQuality = strtod(argv[4], NULL);
		if(GameNode::orderingQuality < 0 || GameNode::orderingQuality > 1){
			cout<<"error ordering quality ("
			    <<GameNode::orderingQuality
			    <<") should be a real number"<<endl
			    <<"in the range [0,1]"<<endl;
			return 1;
		}
		
	}

	//create root node
	GameNode* root;
	root = new GameNode();

	//determine if tree is small enough to print detailed search details
	bool printing = false;
	if(GameNode::branchingMax < 4 && startHeight < 3)
		printing = true;
	
	//search tree with NABS
	int negamaxEvalCount = 0;
	cout<<endl<<"Negamax AlphaBeta evaluation:"
	<<negamaxAlphaBeta(root, startHeight, LOSE, WIN, negamaxEvalCount, printing)<<endl;
	cout<<"Number of static evaluations performed:"<<negamaxEvalCount<<endl<<endl;

	//Search tree using PVS in iterative Deepening Framework
	int pvsEvalCount = 0;
	cout<<"IterativePVS evalutation is:"
	<<iterativeDeepening(root, startHeight, pvsEvalCount, false)<<endl;
	cout<<"Number of static evaluations performed:"<<pvsEvalCount<<endl<<endl;

	//Search tree using PVS with node reordering in iterative Deepening Framework
	int pvsReordEvalCount = 0;
	cout<<"IterativePVS with Node reordering evalutation is:"
	<<iterativeDeepening(root, startHeight, pvsReordEvalCount, true)<<endl;
	cout<<"Number of static evaluations performed:"<<pvsReordEvalCount<<endl<<endl;
	
	//delete tree
	delete root;

	return 0;
}

//function takes "currentNode" as root and searches to depth "height" using NABS with the
//specified alpha and beta values
//staticEvalCount counts the number of static evaluations
//printing determines whether or not node details are printed while the search is carried out
//Code that is conditional on the printing variable has no effect on the result
int negamaxAlphaBeta(GameNode* currentNode, int height, int alpha, int beta,
                     int& staticEvalCount, bool printing)
{
	//identifier and indent variables only used if printing is turned on
	//identifier stores a sequence of integers representing the path from the root node to the 
	//current node with daughter nodes 0 indexed
	// e.g. {0,2,1} would represent the 1st daughter of the 2nd daughter of the root node.
	static vector<int> identifier(1, 0);
	int indent = identifier.size() - 1;//how far to indent the node when printing

	//numDaughters retrieved and stored to save retrieving several times
	int numDaughters = currentNode->getMaxDaughters();

	if(printing)
	{
		//print identifier
		printTabs(indent);
		cout<<"Node: ";
		for(int i = 0; i<identifier.size(); i++)
			cout<<identifier[i]<<"|";
		cout<<endl;
		//print details stored within node
		printTabs(indent);
		currentNode->print();
		cout<<endl;
		//print details stored by AlphaBeta function
		printTabs(indent);
		cout<<"Height: "<<height<<", alpha:"<<alpha<<", beta:"<<beta<<endl;
	}

	//if at leaf node retrieve value of node using static evaluation function
	if(height == 0 || numDaughters == 0)
	{
		int value = currentNode->getStaticValue();
		staticEvalCount++;


		if(printing){
			printTabs(indent);
			cout<<"Calculating node by static evaluation"<<endl;
			printTabs(indent);
			cout<<"Value is "<<value<<endl<<endl;
		}
		return value;
	}//if not at leaf node search values of daughter nodes
	else{
		
		if(printing)
		{
			printTabs(indent);
			cout<<"Calculating node by search"<<endl<<endl;
			identifier.push_back(0);//add a position to the identifier
		}
		
		int temp;
		for(int i = 0; i<numDaughters; i++)
		{	
			identifier.back() = i;//set value of last position in identifier
			GameNode* nextNode = currentNode->retrieveDaughter(i, height-1);
			temp = -negamaxAlphaBeta(nextNode, height-1, -beta, -alpha, staticEvalCount, printing);
			//WOULD DELETE nextNode here in standard negamax alpha beta

			if(temp>=beta){

				if(printing)
				{
					identifier.pop_back();
					printTabs(indent);
					cout<<"Beta value exceeded, no further children will be examined"<<endl;
					printTabs(indent);
					cout<<"Value is "<<temp<<endl<<endl;
				}
				return temp;
			}
			alpha = max(temp, alpha);
		}

		if(printing)
		{
			identifier.pop_back();//remove position from identifier
			printTabs(indent);
			cout<<"Value is "<<alpha<<endl<<endl;
		}
		return alpha;
	}
}


//PVS search function, reOrd determines whether node reordering is enabled
//reordering changes the original tree permanently
int pvs(GameNode* currentNode, int height, int alpha, int beta, int& staticEvalCount, bool reOrd)
{
	int numDaughters = currentNode->getMaxDaughters();
	//if at depth limit return value
	if(height == 0 || numDaughters == 0){
		staticEvalCount++;
		return currentNode->getStaticValue();
	}
	else
	{
			//used if reOrd == true
			//array of node details (index and static evaluation values) used for reordering
			//will be sorted by static evaluation
			nodeDetails daughterOrder[numDaughters];
			int dIterator = 0;
		
			//check if first daughter node is greater than what can be hoped for
			//if it is this node can be safely discounted - return evaluation of daughter
			GameNode* nextNode = currentNode->retrieveDaughter(0, height-1);
			int score = -pvs(nextNode, height-1, -beta, -alpha, staticEvalCount, reOrd);
			if(reOrd){
				//set value of first daughter and increase iterator
				daughterOrder[dIterator].index = dIterator;
				daughterOrder[dIterator].value = score;
				dIterator++;
			}
			//Move would be unmade here in standard PVS
			if(score < beta){
				//if first daughter's score < beta iterate through rest of daughters
				//set lower bound as max of alpha and first daughter's score
				for(int i = 1; i<numDaughters; i++){
					nextNode = currentNode->retrieveDaughter(i, height-1);
					int lowerBound = max(alpha, score);
					int upperBound = lowerBound + 1;

					int temp;
					temp = -pvs(nextNode, height-1, -upperBound, -lowerBound, staticEvalCount, reOrd);

					if(reOrd){
						//set tempNode to same values as node currently being examined.
						daughterOrder[dIterator].index = dIterator;
						daughterOrder[dIterator].value = temp;
					}

					//if nextNode is >= upper bound and < beta find a new value for it
					if(temp>=upperBound && temp < beta){
						temp = -pvs(nextNode, height-1, -beta, -temp, staticEvalCount, reOrd);
							//update tempNode value if more accurate score found
							if(reOrd)
								daughterOrder[dIterator].value = temp;
						//Move would be unmade here in standard PVS
					}
					//increment node iterator
					if(reOrd)
						dIterator++;

					score = max(score, temp);
					if(temp >= beta)
						break;
				}			
				//if more than 1 daughter node
				//sort nodes by static evaluation, then reorder them in the original tree by the sorted order
				if(reOrd && dIterator>1)
				{
					int sortedNodes[dIterator];
					sortNodes(daughterOrder, sortedNodes, dIterator);
					currentNode->reorderNodes(sortedNodes, dIterator);
				}
			}
			return score;
	}
}

//function takes a start node, a depth to search to, a static eval count and a tree search function to use
int iterativeDeepening(GameNode* currentNode, int maxHeight, int& staticEvalCount, bool reOrd)
{
	int depth = 0;
	int guess = 0;
	//simulating test for resources - in a normal iterative deepening framework this test
	//would check if there were sufficient resources (memory or time) available
	while(depth <= maxHeight)
	{
		guess = pvs(currentNode, depth, LOSE, WIN, staticEvalCount, reOrd);
		cout<<"guess at depth "<<depth<<" is "<<guess<<endl;
		depth++;
	}
	return guess;
}


//sort nodes by static evaluation and store the indexes of the sorted nodes in output array
void sortNodes(nodeDetails inputArray[], int outputArray[], int arraySize)
{
	//create output array for storing indices of nodes and initialise it with numerical order
	for(int i = 0; i < arraySize; i++)
		outputArray[i] = i;
	//reorder output array using bubble sort based on the static value of the node referred to by the index
	bool swapped = true;
	while(swapped){
		swapped = false;
		for(int i = 1; i<arraySize; i++){
			if(inputArray[outputArray[i-1]].value < inputArray[outputArray[i]].value){
				int temp = outputArray[i-1];
				outputArray[i-1] = outputArray[i];
				outputArray[i] = temp;
				swapped = true;
			}
		}
	}
}


void printTabs(int numTabs)
{
	for(int i = 0; i<numTabs; i++)
		cout<<'\t';	
}

