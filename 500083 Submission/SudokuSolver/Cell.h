#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Cell
{
public:
	Cell(void);
	~Cell(void);
	// get - set Methods
	void setValue(const int m) { m_value = m; }
	void setBool(const bool g) { m_given = g; }
	void setCanList(const vector<int>&Can) { m_candidateList = Can; }
	int GetValue() const { return m_value; }
	bool GetBool() const { return m_given; }
	vector<int> GetCanList() const { return m_candidateList; }
private:
	//cell objects.
	int m_value;
	bool m_given;
	vector<int> m_candidateList { 1,2,3,4,5,6,7,8,9 };
};
