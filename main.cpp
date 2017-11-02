/*
Julio Berina
CS 301
10/27/17
Project 1
This is a program that determines whether a system
of linear equations has a unique solution and solves
for the unique solution if it has one. Otherwise,
it exits the program.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
	string fname;
	string matrixLine; // Reading lines from iFile
	string holder; // holds string of a matrix [row][col] value
	vector<vector<float>> matrix;
	float* solution;
	int n = 0; // matrix dimensions
	int i, j, k, p;
	float app, sum, mult;

	cout << "Enter file name to read matrix from: ";
	getline(cin, fname);

	ifstream iFile(fname, ifstream::in);
	if (iFile.fail())
		return 1;

	// Determine the dimensions of the matrix
	while (getline(iFile, matrixLine))
	{
		++n;
		stringstream fss(matrixLine);
		vector<float> rowVec;

		while (!fss.eof())
		{
			fss >> holder;
			rowVec.push_back(stof(holder));
		}

		matrix.push_back(rowVec);
	}

	iFile.close();
	solution = new float[n];

	// Initialize solution array to zero
	for (int i = 0; i < n; ++i)
		solution[i] = 0;

	//Fill in the values of the matrix
	for (i = 0; i<(n); i++) 
	{
		app = matrix[i][i];

		//initialization of p
		p = i;

		//find largest no of the columns and row no. of largest no.
		for (k = i + 1; k < n; k++)
		{
			if (fabs(app) < fabs(matrix[k][i])) 
			{
				app = matrix[k][i];
				p = k;
			}
		}

		//swaping the elements of diagonal row and row containing largest no
		for (j = 0; j <= n; j++)
		{
			solution[j] = matrix[p][j];
			matrix[p][j] = matrix[i][j];
			matrix[i][j] = solution[j];
		}

		//calculating triangular matrix
		for (j = i + 1; j < n; j++) 
		{
			mult = matrix[j][i] / matrix[i][i];

			for (k = 0; k <= n; k++)
				matrix[j][k] -= (mult*matrix[i][k]);
		}
	}

	//for calculating value of z,y,x via backward substitution method
	for (i = n - 1; i >= 0; i--)
	{
		sum = 0;
		for (j = i + 1; j < n; j++)
			sum += (matrix[i][j] * solution[j]);

		solution[i] = (matrix[i][n] - sum) / matrix[i][i];
	}

	//display solution
	cout << endl << "Solution:" << endl;
	for (i = 0; i < n; i++)
		cout << "X[" << i + 1 << "] = " << solution[i] << endl;

	cout << endl;

    delete [] solution;
	system("pause");
	return 0;
}