#include <boost/algorithm/string.hpp>
#include <boost/dynamic_bitset.hpp>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Problem.h"

using namespace std;

static class Solution {
public:
	static boost::dynamic_bitset<> CreateSolution(Problem problem) {
		boost::dynamic_bitset<> genome(problem.columns_count()); // all 0's by default
		for (int i = 0; i < problem.rows_count(); i++) {
			vector<int> columns_covering_row = problem.row_coverings()[i];
			int random_number = rand() % columns_covering_row.size() - 1; //zero based
			int random_column = columns_covering_row[random_number];
			genome.set(random_column);

		}

		return genome;
	}

	static boost::dynamic_bitset<> MakeFeasible(boost::dynamic_bitset<> solution, Problem problem) {
		vector<int> covered_rows;

		for (int i = 0; i < solution.size(); i++) {
			if (solution[i]) {
				vector<int> rows = problem.column_coverings()[i];
				covered_rows.insert(covered_rows.end(), rows.begin(), rows.end());
			}
		}

		vector<int> num_of_columns_covering_rows;
		vector<int> uncovered_rows;

		for (int i = 0; i < problem.rows_count(); i++) {
			int count = 0;
			vector<int>::iterator it_covered_rows;
			for (it_covered_rows = covered_rows.begin(); it_covered_rows != covered_rows.end(); ++it_covered_rows) {
				if (*it_covered_rows == (i + 1)) {
					count++;
				}
			}
			if (count == 0) {
				uncovered_rows.push_back(i + 1);
			}

			num_of_columns_covering_rows[i] = count;
		}

		for (int i = 0; i < uncovered_rows.size(); i++) {
			vector<int> row_coverings = problem.row_coverings()[i];

			//TODO: find the first column (in increasing order of j) in Ai that minimizes Cj/|U ^ Bj|
			int column = row_coverings[0];
			solution.set(column);
		}
		return solution;
	}


};