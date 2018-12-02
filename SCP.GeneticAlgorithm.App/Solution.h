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
			vector<int> columnsCoveringRow = problem.row_coverings()[i];
			int random_number = rand() % columnsCoveringRow.size() - 1; //zero based
			int random_column = columnsCoveringRow[random_number];
			genome.set(random_column);

		}

		return genome;
	}


};