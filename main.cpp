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

float determinant(const vector<vector<float>>& matrix);
vector<vector<float>> augmentedMatrix(vector<vector<float>> matrix);
vector<vector<float>> cramerMatrix(vector<vector<float>> matrix, int col); // swaps column of matrix with solution vector
vector<vector<float>> slicedMatrix(vector<vector<float>> matrix, int row, int col); // excludes the row and col provided of the matrix 
vector<float> solve(const vector<vector<float>>& matrix);

int main()
{
    string fname;
    string matrixLine; // Reading lines from iFile
    string holder; // holds string of a matrix [row][col] value
    vector<vector<float>> matrix;
    vector<float> uniqueSolution;

    cout << "Enter file name to read matrix from: ";
    getline(cin, fname);

    ifstream iFile(fname, ifstream::in);
    if (iFile.fail())
        return 1;

    // Determine the dimensions of the matrix
    while (getline(iFile, matrixLine))
    {
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
    uniqueSolution = solve(matrix);

    if (uniqueSolution.empty())
    {
        cerr << "No unique solution!  Exiting program..." << endl;
        return 1;
    }

    cout << "Unique solution:" << endl;

    for (int i = 0; i < uniqueSolution.size(); ++i)
        cout << uniqueSolution[i] << " ";

    cout << endl;

    return 0;
}

float determinant(const vector<vector<float>>& matrix)
{
    float det = 0.0;

    if (matrix.size() == 2)
        return ((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]));
    else
    {
        // Obtain determinant by using cofactors and recursion
        for (int col = 0; col < matrix[0].size(); ++col)
            det += (pow(-1, col) * matrix[0][col] * determinant(slicedMatrix(matrix, 0, col)));
        
        return det;
    }
}

vector<vector<float>> augmentedMatrix(vector<vector<float>> matrix)
{
    for (int row = 0; row < matrix.size(); ++row)
        matrix[row].pop_back();

    return matrix;
}

vector<vector<float>> cramerMatrix(vector<vector<float>> matrix, int col)
{
    float temp = 0.0;
    int solColumn = matrix[0].size() - 1;

    for (int row = 0; row < matrix.size(); ++row)
    {
        temp = matrix[row][col];
        matrix[row][col] = matrix[row][solColumn];
        matrix[row][solColumn] = temp;
        matrix[row].pop_back();
    }

    return matrix;
}

vector<vector<float>> slicedMatrix(vector<vector<float>> matrix, int row, int col)
{
    matrix.erase(matrix.begin()+row);

    for (int r = 0; r < matrix.size(); ++r)
        matrix[r].erase(matrix[r].begin()+col);

    return matrix;
}

vector<float> solve(const vector<vector<float>>& matrix)
{
    vector<float> unique;
    float det = determinant(augmentedMatrix(matrix));
    int colSize = matrix[0].size() - 1; // take any row of the matrix to get column size minus solution vector

    if (det != 0)
    {
        for (int c = 0; c < colSize; ++c)
            unique.push_back((determinant(cramerMatrix(matrix, c)) / det));
    }

    return unique; // Returns unique whether or not a unique solution exists
}