/*Craps.cpp - Program to simulate 1000 games of craps and compute probabilities of winning
* based on those games
*Author - John Kilfeather
*Last Updated - 30 Mar 2011
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>


using namespace std;

//function to roll numberToRoll dice and return their sums
//as well as storing the individual dice values
int rollDice(int diceVals[], int numberToRoll=2);

enum Status {CONTINUE, WON, LOST};

const int TOTAL_GAMES = 1000;//total number of games to be played

int main()
{

  int totalWins = 0;//Total number of players wins
  //wins/losses in each round (round 1 indexed to 0, rounds after 20 indexed at 19)
  int winRoundCount[20];
  int loseRoundCount[20];
  //current round of dice rolls
  int round = 0;
  
  int totalLength = 0;//Total length - total number of rounds across all games
  
  int sum;
  int myPoint;
  int diceVals[2];

  Status gameStatus;
  
  /*Seed random num generator*/
  srand(time(0));
  
  /*Initialise win and lose counts to 0*/
  for(int i = 0; i<20;i++)
  {
		winRoundCount[i] = 0;
		loseRoundCount[i] = 0;
  }
  
  
  /*Run game TOTAL_GAMES times*/
  for(int i = 0; i<TOTAL_GAMES; i++)
  {

		//Get and print out player rolls*/
		sum = rollDice(diceVals);
		cout << "Player rolled " << diceVals[0] << " + " << diceVals[1] << endl;

		/*Check first round win/lose/point conditions*/
		switch(sum)
		{
			case 7:
			case 11:
				gameStatus = WON;
				break;
			case 2:
			case 3:
			case 12:
				gameStatus = LOST;
				break;
			default:
				gameStatus = CONTINUE;
				myPoint = sum;
				cout << "Point is " << myPoint << endl;
				break;
		}
	
		/*Continue with game if no win/lose value rolled in first round, until point or lose value reached*/
		while (gameStatus == CONTINUE)
		{
			round++;
			sum = rollDice(diceVals);
			cout << "Player rolled " << diceVals[0] << " + " << diceVals[1] << endl;
			if (sum==myPoint)
			gameStatus=WON;
			else if (sum==7)
			gameStatus = LOST;
		}
	
		/*If won - increment total wins, increment total length by round number, increase winRoundCount for that round*/
		if (gameStatus == WON)
		{
			totalWins++;
			totalLength += (round+1);
			if(round>19)
			round = 19;
			winRoundCount[round]++;
			round = 0;
			cout << "Player wins" << endl<<endl;
		}
		/*else (if lost) - increment total length by round number, increase loseRoundCount for that round*/
		else
		{
			totalLength += (round+1);
			if(round>19)
			round = 19;
			loseRoundCount[round]++;
			round = 0;
			cout << "Player loses" << endl<<endl;
		}
  }
  
  //Print out how many games are won and lost after each round  
  cout<<endl<<"Wins and losses in each round"<<endl;
  for(int i = 0; i<20;i++)
  {
	cout<<"Round "<<setw(2)<<i+1<<": Wins "<< winRoundCount[i]<<", Losses "<< loseRoundCount[i]<<endl;
  }
  
  //Print out overall probability of winning
  cout<<endl<<"Probability of winning: " << (static_cast<double>(totalWins))/TOTAL_GAMES<<endl;
  
  
  //Print out average length
  cout<<endl<<"Average Length: "<<static_cast<double>(totalLength) / TOTAL_GAMES<<endl;  

  

  //Print out probability of winning each round
  cout<<endl<<"Probability of winning if game ends in that round: "<<endl;
  for(int i = 0; i<20;i++)
  {

		cout<<"Round "<<setw(2)<<i+1;
		if(i==19)
			cout<<"(or after)";
		cout<<": ";
		if( (winRoundCount[i] + loseRoundCount[i]) > 0)
			cout<<static_cast<double>(winRoundCount[i])/(winRoundCount[i] + loseRoundCount[i])<<endl;
		else
			cout<<"No Data"<<endl;
  }  
  
  cout<<"The above probabilities should show that the chance of winning decreases significantly after round 1"<<endl;
  
  return 0;
}

int rollDice(int diceVals[], int numberToRoll)
{
	
	int sum = 0;
	/*roll numberToRoll dices, and add them to get the sum*/
	for(int i = 0; i < numberToRoll; i++)
	{
		diceVals[i] = 1 + rand()%6;
		sum += diceVals[i];
	}

	return sum;
}






  



  

  

  
