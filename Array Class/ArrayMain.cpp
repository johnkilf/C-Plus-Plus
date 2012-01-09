/*
 * ArrayMain.cpp
 * Program to test the functionality of the Array Class Created in Array.cpp
 *
 *  Created on: 13 Apr 2011
 *      Author: john
 */

#include<iostream>
#include"Array.h"

using namespace std;

int main(int argc, char*argv[])
{
	  Array a(2,6);
	  Array b(2,2,3);
	  Array c;

	  for (int i=0;i<2;i++)
	    for (int j=0;j<6;j++)
	      a(i,j) = i+j;

	  for (int i=0;i<2;i++)
	    for (int j=0;j<2;j++)
	      for (int k=0;k<3;k++)
		b(i,j,k) = i*j+k;


		cout<<"b (2*2*3) is"<<endl<<b;
	  b.reshape(2,6);
		cout<<"b reshaped (2*6) is"<<endl<<b;

	  c = a*b;
		cout <<"c is"<<endl<<c;
		cout<<"c transposed is"<<endl<<c.transpose();


	  return 0;

}
