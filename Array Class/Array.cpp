/*
 * Array.cpp
 *
 *  Created on: 13 Apr 2011
 *      Author: john
 */


#include<iostream>
#include<iomanip>
#include<cstdlib>


#include"Array.h"

using namespace std;


ostream& operator<<(ostream& outstream, Array input)
{
	//Printing 3d matrices
	if(input.dimensions[2]>0)
	{
		for(int i=0;i<input.dimensions[0];i++){
			for(int j=0;j<input.dimensions[1];j++){
				for(int k=0; k<input.dimensions[2]; k++){
					outstream<<setw(3)<<input.dubs[(i*input.dimensions[1]*input.dimensions[2]) +(j*input.dimensions[2])+k]<<" ";
				}
				outstream<<'|';
			}
			outstream<<endl;
		}
	}
	//Printing 2d matrices
	else if(input.dimensions[1]>0){
		for(int i=0; i<input.dimensions[0];i++){
			for(int j=0; j<input.dimensions[1];j++){
				outstream<<setw(3)<<input.dubs[(i*input.dimensions[1])+j]<<" ";
			}
			outstream<<endl;
		}
	}
	//Printing 1d matrices
	else{
		for(int i=0; i<input.dimensions[0];i++)
			outstream<<setw(3)<<input.dubs[i]<<" ";
		outstream<<endl;
	}

	return outstream;
}


/*Default constructor*/
Array::Array()
{
	dimensions[0]=dimensions[1]=dimensions[2]=0;
}


/*1 dimensional constructor*/
Array::Array(int dim1)
{
	if(dim1 <= 0){
		cout<<"Invalid intialisation";
		exit(1);
	}
	dimensions[0]=dim1;
	dimensions[1]=dimensions[2]=0;
	dubs = new double[dim1];
}

/*2 dimensional constructor*/
Array::Array(int dim1, int dim2)
{
	if(dim1 <= 0 || dim2 <= 0){
		cout<<"Invalid initialisation";
		exit(1);
	}
	dimensions[0]=dim1;
	dimensions[1]=dim2;
	dimensions[2]=0;

	dubs = new double[dim1*dim2];
}

/*3 dimensional constructor*/
Array::Array(int dim1, int dim2, int dim3)
{
	if(dim1 <= 0 || dim2 <= 0 || dim3<=0){
		cout<<"Invalid initialisation";
		exit(1);
	}
	dimensions[0]=dim1;
	dimensions[1]=dim2;
	dimensions[2]=dim3;

	dubs = new double[dim1*dim2*dim3];
}

/*Copy constructor*/
Array::Array(const Array& input)
{
	//set dimensions the same
	dimensions[0] = input.dimensions[0];
	dimensions[1] = input.dimensions[1];
	dimensions[2] = input.dimensions[2];

	//set doubles the same-loop conditions depend on dimensions
	if(dimensions[2]>0)
	{
		dubs = new double[dimensions[0]*dimensions[1]*dimensions[2]];
		for(int i=0;i<dimensions[0]*dimensions[1]*dimensions[2];i++)
			dubs[i] = input.dubs[i];
	}
	else if(dimensions[1]>0)
	{
		dubs = new double[dimensions[0]*dimensions[1]];
		for(int i=0;i<dimensions[0]*dimensions[1];i++)
			dubs[i] = input.dubs[i];

	}
	else
	{
		dubs = new double[dimensions[0]];
		for(int i=0;i<dimensions[0];i++)
			dubs[i] = input.dubs[i];
	}

}

/*Destructor*/
Array::~Array(){
	delete [] dubs;
}

/*Assignment operator*/
Array Array::operator=(const Array& input)
{
	//if memory has already been allocated delete it:
	if(dimensions[0]>0){
		delete [] dubs;
	}
	//set dimensions the same
	dimensions[0] = input.dimensions[0];
	dimensions[1] = input.dimensions[1];
	dimensions[2] = input.dimensions[2];

	//set doubles the same-loop conditions depend on dimensions
	if(dimensions[2]>0)
	{
		dubs = new double[dimensions[0]*dimensions[1]*dimensions[2]];
		for(int i=0;i<dimensions[0]*dimensions[1]*dimensions[2];i++)
			dubs[i] = input.dubs[i];
	}
	else if(dimensions[1]>0)
	{
		dubs = new double[dimensions[0]*dimensions[1]];
		for(int i=0;i<dimensions[0]*dimensions[1];i++)
			dubs[i] = input.dubs[i];

	}
	else
	{
		dubs = new double[dimensions[0]];
		for(int i=0;i<dimensions[0];i++)
			dubs[i] = input.dubs[i];
	}

	return *this;

}

double& Array::operator()(int dim1)
{
	//check to see if it's a 2d or 3d array
	if(dimensions[1]>0){
		cout<<"Not allowed: array is of wrong dimension"<<endl;
		exit(1);
	}//check to see if indexes are within array bounds
	else if(dim1>dimensions[0] || dim1<0 ){
		cout<<"Not allowed: Index out of bounds"<<endl;
		exit(1);
	}
	else
		return dubs[dim1];
}



double& Array::operator()(int dim1, int dim2)
{
	//check to see if it's a 1d or 3d array
	if(dimensions[2]>0 || dimensions[1]==0){
		cout<<"Not allowed: array is of wrong dimension"<<endl;
		exit(1);
	}//check to see if indexes are within array bounds
	else if(dim1>dimensions[0] || dim2 > dimensions[1] || dim1<0 || dim2<0){
		cout<<"Not allowed: Index out of bounds"<<endl;
		exit(1);
	}
	else
		return dubs[dim1*dimensions[1] + dim2];
}

double& Array::operator()(int dim1, int dim2, int dim3)
{
	//check to see if it's a 1d or 2d array
	if(dimensions[2]==0){
		cout<<"Not allowed: array is of wrong dimension"<<endl;
		exit(1);
	}//check to see if indexes are within array bounds
	else if(dim1>dimensions[0] || dim2 > dimensions[1] || dim3 > dimensions[2] || dim1<0 ||dim2<0 ||dim3<0){
		cout<<"Not allowed: Index out of bounds"<<endl;
		exit(1);
	}
	else
		return dubs[dim1*dimensions[1]*dimensions[2] + dim2*dimensions[2] + dim3];
}

Array Array::operator*(Array input)
{
	//Check dimensions are the same
	if(dimensions[0]!= input.dimensions[0] || dimensions[1]!= input.dimensions[1] || dimensions[2]!= input.dimensions[2])
	{
		cout<<"Unable to multiply as matrix dimensions are not the same"<<endl;
		exit(1);
	}
	//multiplying 3d matrices
	else if(dimensions[2]>0){
		Array result(dimensions[0], dimensions[1], dimensions[2]);
		for(int i = 0; i<dimensions[0]; i++){
			for(int j = 0; j<dimensions[1]; j++){
				for(int k = 0; k<dimensions[2]; k++){
					result(i,j,k) = dubs[(i*dimensions[1]*dimensions[2]) +(j*dimensions[2])+k] * input(i,j,k);
				}
			}
		}
		return result;
	}
	//multiplying 2d matrices
	else if(dimensions[1]>0){
		Array result(dimensions[0], dimensions[1]);
		for(int i=0; i<dimensions[0];i++){
			for(int j=0; j<dimensions[1]; j++){
				result(i,j) = dubs[i*dimensions[1] + j] * input(i,j);
			}
		}

		return result;
	}
	//multiplying 1d matrices
	else{
		Array result(dimensions[0]);
		for(int i=0; i<dimensions[0];i++)
			result(i) = dubs[i]*input(i);
		return result;
	}
}


void Array::reshape(int dim1)
{
	//resizing from 3d to 1d
	if(dimensions[2]>0 && dim1 == dimensions[0]*dimensions[1]*dimensions[2]){
		dimensions[0]=dim1;
		dimensions[1]=0;
		dimensions[2]=0;
	}//resizing from 2d to 1d
	else if(dimensions[1]>0 && dim1 == dimensions[0]*dimensions[1])
	{
		dimensions[0]=dim1;
		dimensions[1]=0;
	}//No 1d to 1d resize as nothing changes in that case
	else
	{
		cout<<"Unable to reshape, dimensions supplied do not match size of matrix"<<endl;
	}

}


void Array::reshape(int dim1, int dim2)
{
	//resizing from 3d to 2d
	if(dimensions[2]>0 && dim1*dim2 == dimensions[0]*dimensions[1]*dimensions[2]){
		dimensions[0]=dim1;
		dimensions[1]=dim2;
		dimensions[2]=0;
	}//resizing from 2d to 2d
	else if(dimensions[1]>0 && dim1*dim2 == dimensions[0]*dimensions[1])
	{
		dimensions[0]=dim1;
		dimensions[1]=dim2;
	}//resizing from 1d to 2d
	else if(dim1*dim2 == dimensions[0])
	{
		dimensions[0]=dim1;
		dimensions[1]=dim2;
	}
	else
	{
		cout<<"Unable to reshape, dimensions supplied do not match size of matrix"<<endl;
	}
}

void Array::reshape(int dim1, int dim2, int dim3)
{
	//resizing from 3d to 3d
	if(dimensions[2]>0 && dim1*dim2*dim3 == dimensions[0]*dimensions[1]*dimensions[2]){
		dimensions[0]=dim1;
		dimensions[1]=dim2;
		dimensions[2]=dim3;
	}//resizing from 2d to 3d
	else if(dimensions[1]>0 && dim1*dim2*dim3 == dimensions[0]*dimensions[1])
	{
		dimensions[0]=dim1;
		dimensions[1]=dim2;
		dimensions[2]=dim3;
	}//resizing from 1d to 3d
	else if(dim1*dim2*dim3 == dimensions[0])
	{
		dimensions[0]=dim1;
		dimensions[1]=dim2;
		dimensions[2]=dim3;
	}
	else
	{
		cout<<"Unable to reshape, dimensions supplied do not match size of matrix"<<endl;
	}

}

Array& Array::transpose()
{

	if(dimensions[2] > 0 || dimensions [1]==0){
		cout<<"Unable to transpose as matrix is not 2 dimensional"<<endl;
	}
	else{
		//Declare a 2d array the same size as the existing matrix to temporarily store variables while they are being switched
		double tempdubs[dimensions[1]][dimensions[0]];

		//Store the variables in this new array in the correct order
		for(int i = 0; i<dimensions[0];i++){
			for(int j=0; j<dimensions[1]; j++){
				tempdubs[j][i] = dubs[i*dimensions[1] + j];
			}
		}

		//Reorder the original array like the temporary one
		for(int i = 0; i<dimensions[1];i++){
			for(int j=0; j<dimensions[0]; j++){
				dubs[i*dimensions[0] + j] = tempdubs[i][j];
			}
		}

		//reorder dimensions
		int tempDimension = dimensions[1];
		dimensions[1]=dimensions[0];
		dimensions[0]=tempDimension;

	}
	return *this;
}



