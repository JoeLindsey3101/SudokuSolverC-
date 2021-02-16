#include "SudokuPuzzle.h"
#include "Cell.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <vector>


SudokuPuzzle::SudokuPuzzle() {
	// Add code to initialise the SudokuPuzzle object
}

void SudokuPuzzle::solve(const char filenameIn[]) {
	// Read puzzle from text file
	readPuzzle(filenameIn);

	// Get start time
	const auto startTime = std::chrono::high_resolution_clock::now();
	//Loop for Solve Method
	while (solved != true)
	{
		solver();
		passesThru++;
	}
	//display debugging statements.
	std::cout << "Cells Solved: " << cellSolved << std::endl;
	std::cout << "Passes Through Grid: " << passesThru << std::endl;
	std::cout << "Amount of Considered values: " << consideredVal << std::endl;
	// Get end time
	const auto endTime = std::chrono::high_resolution_clock::now();
	const auto duration = (endTime - startTime).count();
	// Sample timing output in nanoseconds
	std::cout << duration << "ns" << std::endl;

	// Output the solved puzzle
	output();
}

void SudokuPuzzle::solver()
{
	//check 9 x 9 grid
	for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				//if x + y of grid value == 0, create candidate list for cell.
				if (m_grid[i][j].GetValue() == 0)
				{
					CheckAll(i, j);
				}
			}
		}
	//method call to check if puzzle solved.
	FindBlank();
}
void SudokuPuzzle::FindBlank()
{
	int Solved = 0;
	//check 9 x 9
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			//checks cells to see if value isnt 0 and increment variable 
			if (m_grid[i][j].GetValue() != 0)
			{
				Solved++;
			}
		}
	}
	//set bool value for while loop to true or false 
	if (Solved == 81)
	{
		solved = true;
	}
	else if (solved != 81)
	{
		solved = false;
	}
}
void SudokuPuzzle::checkRow(int row, int col)
{
	//read in candidate list to new vector
	vector<int> FoundNums = m_grid[row][col].GetCanList();
	//store the original column value
	const int originalCol = col;
	//check column for values, if value isnt 0, remove from new vector
	for (col = 0; col < 9; col++)
	{
		const int FoundNum = m_grid[row][col].GetValue();
		if (FoundNum != 0)
		{
			FoundNums.erase(std::remove(FoundNums.begin(), FoundNums.end(), FoundNum), FoundNums.end());
		}
	}
	//upload new vector to candidate list
	m_grid[row][originalCol].setCanList(FoundNums);
}
void SudokuPuzzle::checkCol(int row, int col)
{
	//read in candidate list to new vector
	vector<int> FoundNums = m_grid[row][col].GetCanList();
	//store the original row value
	const int originalRow = row;
	//check row for values, if value isnt 0, remove from new vector
	for (row = 0; row < 9; row++)
	{
		const int FoundNum = m_grid[row][col].GetValue();
		if (FoundNum != 0)
		{
			FoundNums.erase(std::remove(FoundNums.begin(), FoundNums.end(), FoundNum), FoundNums.end());
		}
	}
	//upload new vector to candidate list
	m_grid[originalRow][col].setCanList(FoundNums);
}
void SudokuPuzzle::checkBox(int row, int col)
{
	//read in candidate list to new vector
	vector<int> FoundNums = m_grid[row][col].GetCanList();
	//store original row and create new value for a stored row
	const int originalRow = row;
	int storedrow = 0;
	//set the value to 0, 3, 6 for the 3 x 3 box the current cell is in
	if (row == 0 || row == 1 || row == 2)
	{
		row = 0;
		storedrow = row + 3;

	}
	else if (row == 3 || row == 4 || row == 5)
	{
		row = 3;
		storedrow = row + 3;

	}
	else if (row == 6 || row == 7 || row == 8)
	{
		row = 6;
		storedrow = row + 3;

	}
	//store original column and create new value for a stored column
	const int originalCol = col;
	int storedcol = 0;
	//set the value to 0, 3, 6 for the 3 x 3 box the current cell is in
	if (col == 0 || col == 1 || col == 2)
	{
		col = 0;
		storedcol = col + 3;

	}
	else if (col == 3 || col == 4 || col == 5)
	{
		col = 3;
		storedcol = col + 3;

	}
	else if (col == 6 || col == 7 || col == 8)
	{
		col = 6;
		storedcol = col + 3;
		
	}
	int FoundNum;

	//checks 3 x 3 for values that dont = 0, remove from new vector
	for (row; row < storedrow; row++)
	{
		for (col; col < storedcol; col++)
		{
			FoundNum = m_grid[row][col].GetValue();
			if (FoundNum != 0)
			{
				FoundNums.erase(std::remove(FoundNums.begin(), FoundNums.end(), FoundNum), FoundNums.end());
			}
		}
		// set the col value back to the starting col value.
		col = storedcol - 3;
	}
	//upload new vector to candidate list
	m_grid[originalRow][originalCol].setCanList(FoundNums);
}

void SudokuPuzzle::CheckAll(int row, int col)
{
	//main method calls to check current row, column and 3 x 3 box to generate candidate list
	checkRow(row, col);
	checkCol(row, col);
	checkBox(row, col);
	//display to console candidate list for each cell.
	const vector<int> FoundNums = m_grid[row][col].GetCanList();
	//count each considered value inside a candidate list
	consideredVal += FoundNums.size();
	//method call
	checkList(row, col);
}

void SudokuPuzzle::checkList(int row, int col)
{
	//read candidate list to new vector
	vector<int> FoundNums = m_grid[row][col].GetCanList();
	//checks to see if candidate list has 1 value.
	if (FoundNums.size() == 1)
	{
		//set cell value to candidate list num.
		const int possNum = FoundNums.front();
		m_grid[row][col].setValue(possNum);
		//increment amount of cell solved and how many cell solved variables.
		cellSolved++;
		solved++;
	}
}
void SudokuPuzzle::readPuzzle(const char filenameIn[]) {
	using namespace std;
	//create ifstream 
	ifstream fin(filenameIn);
	//if the ifstream is open.
	if (fin.is_open())
	{
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				//read the file in to val, set the current cell x and y to that value
				int val;
				bool boo;
				fin >> val;
				m_grid[row][col].setValue(val);
				//if the value is 0, the number was generated by program (false) and if it is not 0 the value was already in the file (true)
				if (val == 0)
				{
					boo = false;
					m_grid[row][col].setBool(boo);
				}
				else if (val != 0)
				{
					boo = true;
					m_grid[row][col].setBool(boo);
				}
			}
		}
	}
	//close the ifstream.
	fin.close();
}
void SudokuPuzzle::output() const {
	using namespace std;
	//create fout stream
	ofstream fout("sudoku_solution.txt");	
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			//output value from cell to variable and output that variable to fout
			const int val = m_grid[row][col].GetValue();
			fout << val << " ";
		}
		fout << endl;
	}
	fout.close();
}