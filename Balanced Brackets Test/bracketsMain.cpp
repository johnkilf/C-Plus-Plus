/*
 * bracketsMain.cpp
 * Program to test whether brackets are balanced or not
 * Tests to check that {,[, and ( brackets are closed
 * and in the correct order
 *
 *  Created on: 18 Apr 2011
 *      Author: John Kilfeather
 */


#include <stack>
#include <iostream>
#include <cstring>

using namespace std;
const int MAXLINE=100;

int main()
{
	char input_line[MAXLINE];
	stack<char> mystack;
	int length, i;

	// read a line from the screen
	cout<<"Input string to test for balanced brackets"<<endl;
	cin >> input_line;
	length = strlen(input_line);


	i=0;

	//balanced is set to automatically true and switched if found to be false at any instance
	bool balanced = true;

	//loop through sentence testing for misplaced closing brackets
	while (i<length && balanced)
	{
		//if opening bracket found add it to top of stack
		if (input_line[i] == '(' || input_line[i] == '[' || input_line[i] == '{' )
			mystack.push(input_line[i]);
		else {
			//test for closing brackets - if the same as the last added opening bracket then
			//remove that opening bracket from the stack, otherwise set balanced to false
			if (input_line[i] == ')')
			{
				if (mystack.empty() || mystack.top() != '(')
					balanced=false;
				else
					mystack.pop();
			}
			else if(input_line[i] == ']')
			{
				if (mystack.empty() || mystack.top() != '[')
					balanced=false;
				else
					mystack.pop();
			}
			else if(input_line[i] == '}')
			{
				if (mystack.empty() || mystack.top() != '{')
					balanced=false;
				else
					mystack.pop();
			}
		}
		i++;
	}
	//test if opening brackets have been added to the stack which were never closed
	if(!mystack.empty())
		balanced = false;

	if(balanced)
		cout << "Parentheses are balanced.\n";
	else
		cout << "Parentheses are not balanced.\n";

	return 0;
}
