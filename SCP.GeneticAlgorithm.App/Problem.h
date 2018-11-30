#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Utilities.h"

using namespace std;

class Problem
{
private:
	int rows;
	int columns;
	vector<int> costs;
	vector<vector<int>> rowCoverings; // the set of columns that covers row
	vector<vector<int>> columnCoverings; // the set of rows that covers column

public:
	int getRows() {
		return rows;
	}

	void setRows(int rows) {
		this->rows = rows;
	}

	int getColumns() {
		return columns;
	}

	void setColumns(int columns) {
		this->columns = columns;
	}

	vector<int> getCosts() {
		return costs;
	}

	void setCosts(vector<int> costs) {
		this->costs = costs;
	}

	vector<vector<int>> getRowCoverings() {
		return rowCoverings;
	}

	void setRowCoverings(vector<vector<int>> rowCoverings) {
		this->rowCoverings = rowCoverings;
	}

	vector<vector<int>> getColumnCoverings() {
		return columnCoverings;
	}

	void setColumnCoverings(vector<vector<int>> columnCoverings) {
		this->columnCoverings = columnCoverings;
	}


};