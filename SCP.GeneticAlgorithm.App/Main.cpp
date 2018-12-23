#include <iostream>
#include "Contants.h"
#include "Problem.h"
#include "GeneticAlgorithm.h"

using namespace std;
int main()
{
	Problem problem;
	problem.ReadFile(FILE_DIRECTORY);
	//GeneticAlgorithm ga(0, problem, 100, 60, 2);
	//cout << "Initialising initial population" << endl;
	//ga.Initialize();
	//cout << "Completed initializing initial population" << endl;
	//ga.Train();

#pragma region print columns and rows count
	cout << "columns_count: " << problem.columns_count() << endl;
	cout << "rows_count: " << problem.rows_count() << endl;
#pragma endregion

#pragma region print costs
	vector<int>::iterator it_costs;

	cout << "Printing costs:" << endl;
	vector<int> costs = problem.costs();
	for (it_costs = costs.begin(); it_costs != costs.end(); ++it_costs)
	{
		std::cout << *it_costs << " ";
	}
	cout << endl;
#pragma endregion

#pragma region print row coverings
	vector<int>::iterator it_row_coverings;

	cout << "Printing row_coverings:" << endl;

	for (size_t i = 0; i < problem.row_coverings().size() - 1; i++) {
		vector<int> single_row_covering = problem.row_coverings()[i];
		for (it_row_coverings = single_row_covering.begin(); it_row_coverings != single_row_covering.end(); ++it_row_coverings)
		{
			std::cout << *it_row_coverings << " ";
		}
		cout << endl;
	}
	cout << endl;
#pragma endregion

#pragma region print column coverings
	vector<int>::iterator it_column_coverings;

	cout << "Printing column_coverings:" << endl;

	for (size_t i = 0; i < problem.column_coverings().size() - 1; i++) {
		vector<int> single_column_covering = problem.column_coverings()[i];
		for (it_column_coverings = single_column_covering.begin(); it_column_coverings != single_column_covering.end(); ++it_column_coverings)
		{
			std::cout << *it_column_coverings << " ";
		}
		cout << endl;
	}
	cout << endl;
#pragma endregion



	return 0;
}