/*Author: John Kilfeather
*node.h - class to simulate a node in a game tree
*/

#include <iostream>
#include <stdlib.h>

using namespace std;

const int WIN = 1000;
const int LOSE = -1000;

class GameNode{

	public:
	//static variables used in creating each node
	static int branchingMin;
	static int branchingMax;
	static double orderingQuality;	
		
	//Constructors
	GameNode();//for root node
	GameNode(int parentTrue, int height, bool isBest=false);//for all other nodes

	//Destructor
	~GameNode();//No copy constructor currently defined - Do not make shallow copies of nodes 

	//accessor/mutator function - creates daughter node if one does not already exist
	GameNode* retrieveDaughter(int i, int height);

	//Accessors
	int getMaxDaughters();
	int getStaticValue();
		
	//Mutator
	void reorderNodes(int newOrder[], int numNodes);

	//printing function
	void print();

	private:
	int staticValue;
	int trueValue;

	int maxDaughters;//total number of daughters possible for node
	int initializedDaughters;//number of daughters that have been created
	int bestDaughter;//index of best daughter
	GameNode** daughters;//pointer to array of daughter nodes
};


