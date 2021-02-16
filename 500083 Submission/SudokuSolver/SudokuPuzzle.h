#pragma once
#include "Cell.h"
// Add your code here

class SudokuPuzzle {
public:
	SudokuPuzzle();
	void solve(const char filenameIn[]);
private:
	//method definitions
	void output() const;
	void readPuzzle(const char filenameIn[]);
	void checkRow(int row, int col);
	void checkCol(int row, int col);
	void checkBox(int row, int col);
	void CheckAll(int row, int col);
	void checkList(int row, int col);
	void FindBlank();
	void solver();
	//cell 9 x 9 array.
	Cell m_grid[9][9];
	
	// debugging variables
	bool solved = false;
	int cellSolved = 0;
	int passesThru = 0;
	int consideredVal = 0;
};

