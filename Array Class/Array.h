/*
 * Array.h - general multidimensional array of doubles for 1d,2d, and 3d matrices.
 * Provides similar functionality to standard c++ arrays with a few additional features
 * as an exercise in Object Orientated Programming
 *
 * Matrix elements accessed using () operator
 * e.g: myArray(2,3)=5;
 * Sets the third element in the second row of a 2d matrix to 5
 *
 * Internally the matrix elements are all stored in a single array of doubles - "dubs"
 * The size of each of the dimensions is stored in an array of integers - "dimensions"
 * Whether a matrix is of 1, 2, or 3 dimensions can be found by checking  if the size of
 * a dimension is > 0
 *
 * Multidimensional arrays are stored in row major order.
 * e.g. The element myArray(x,y,z) is stored at the location:
 * myArray.dubs[(x * dimensions[1] * dimensions[2]) + (y * dimensions[2]) + z]
 *
 *  Created on: 13 Apr 2011
 *      Author: john
 */

using namespace std;

class Array
{
	/*Printing function*/
	friend ostream& operator<<(ostream& outstream, Array input);

	public:
		//CONSTRUCTORS
		Array();
		Array(int dim1);
		Array(int dim1, int dim2);
		Array(int dim1, int dim2, int dim3);
		Array(const Array&);
		//DESTRUCTOR
		~Array();
		//OPERATORS
		Array operator=(const Array& input);
		double& operator()(int dim1);
		double& operator()(int dim1, int dim2);
		double& operator()(int dim1, int dim2, int dim3);
		Array operator*(Array input);
		//METHODS
		void reshape(int dim1);
		void reshape(int dim1, int dim2);
		void reshape(int dim1, int dim2, int dim3);
		Array& transpose();

	private:
		int dimensions[3];
		double* dubs;
};


