/*display20.cpp: Program to display a file 20 lines at a time
Authors: John Kilfeather
Last Modified: 1/Mar/2010
***/
#include <iostream>
#include <fstream>

using namespace std;

/*function that prints 20 lines of a file*/
int printlines(fstream &filepath);

int main(int argc, char *argv[])
{

	fstream fp1;/*File that will be displayed*/
	char user_input = '\0';/*used to check if user wants to quit*/
	
	if(argc<2)
	{
		cout<<"Must supply file name as argument"<<endl;
		return 1;
	}
	
	/*open file and test to see if it succeeded*/
	fp1.open(argv[1], ios::in);
	if(fp1.fail())
	{
		printf("file failed to open");
		return 1;
	}
	else
	{
	
		/*Print 20 lines then wait for user input
			-if user inputs 'q' end the loop and the program
			-if user presses return print the next 20 lines
		*/
		printlines(fp1);
		while(user_input != 'q')
		{
			cout<<"Enter q to quit or press return to display more: ";
			user_input = cin.get();
			if(user_input ==  '\n')
			{
				if(printlines(fp1)==1)
					return 0;
			}
		}
			
	}	
	
	/*Close file*/
	fp1.close();
	return 0;
}

int printlines(fstream &filepath)
{
	int return_count = 0;/*counts number of return characters, i.e. the number of lines*/
	char read_char;/*character currently being read*/
	
	/*loop until return_count is 20 reading each character from the file and printing it to the screen*/
	while(return_count<20)
	{
		/*Read character from file*/
		filepath.get(read_char);
		
		/*check to see if end of file*/
		if(!filepath.eof())
		{
			/*if character is a return char increase return count*/
			if(read_char == '\n')
			{
				return_count++;
			}
			/*print the character*/
			cout<<read_char;
			
		}
		else
		{
			/*If end of file terminate program*/
			cout<<endl<<"END OF FILE";
			filepath.close();
			return 1;
		}
	}
	return 0;
}