#pragma once
#include <boost/algorithm/string.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Problem
{
private:
	int rows_count_;
	int columns_count_;
	vector<int> costs_;
	vector<vector<int>> row_coverings_; // the set of columns that covers row
	vector<vector<int>> column_coverings_; // the set of rows that covers column

public:
	// accessors and mutators
	int rows_count() {
		return rows_count_;
	}

	void rows_count(int rows_count) {
		this->rows_count_ = rows_count;
	}

	int columns_count() {
		return columns_count_;
	}

	void columns_count(int columns_count) {
		this->columns_count_ = columns_count;
	}

	vector<int> costs() {
		return costs_;
	}

	void costs(vector<int> costs) {
		this->costs_ = costs;
	}

	vector<vector<int>> row_coverings() {
		return row_coverings_;
	}

	void row_coverings(vector<vector<int>> row_coverings) {
		this->row_coverings_ = row_coverings;
	}

	vector<vector<int>> column_coverings() {
		return column_coverings_;
	}

	void column_coverings(vector<vector<int>> column_coverings) {
		this->column_coverings_ = column_coverings;
	}

	// member functions
	void ReadFile(string input_file) {

		cout << "inputFile" << input_file << endl;

		ifstream file(input_file);

		if (file.is_open()) {

			cout << "file is opened" << endl;

			string size;
			vector<string> sizes;
			vector<int> costs;
			int counter = 0;

			getline(file, size);
			boost::algorithm::split(sizes, size, boost::is_any_of(" "));
			rows_count(stoi(sizes[0]));
			columns_count(stoi(sizes[1]));


			// read input file and store the costs into private member "costs"
			while (counter < columns_count_) {
				string line;
				vector<string> temp_costs;

				getline(file, line);
				cout << "line: " << line << endl;
				boost::trim(line);
				boost::algorithm::split(temp_costs, line, boost::is_any_of(" "));
				for (size_t i = 0; i < temp_costs.size(); i++) {
					costs.push_back(stoi(temp_costs[i]));
					counter++;
				}
			}

			this->costs(costs);

			// set row_coverings
			for (int i = 0; i < this->rows_count(); i++) {
				string line;
				vector<string> str_num_of_columns;
				getline(file, line);
				boost::trim(line);
				boost::algorithm::split(str_num_of_columns, line, boost::is_any_of(" "));

				// number of columns in the current set
				int num_of_columns = stoi(str_num_of_columns[0]);


				int col_counter = 0;
				vector<int> single_row_coverings; //

				// read the set of columns that cover each rows (alpha[i]), aka "row_covering"
				while (col_counter < num_of_columns) {
					vector<string> temp_columns;
					getline(file, line);
					boost::trim(line);
					boost::algorithm::split(temp_columns, line, boost::is_any_of(" "));

					for (size_t j = 0; j < temp_columns.size(); j++) {
						single_row_coverings.push_back(stoi(temp_columns[j]));
						col_counter++;
					}
				}

				this->row_coverings_.push_back(single_row_coverings);
			}


			// set column_coverings
			for (int i = 1; i < this->columns_count(); i++) {
				vector<int> single_column_coverings;
				for (int j = 1; j < this->rows_count(); j++) {
					vector<int> single_row_coverings = this->row_coverings_[j - 1];

					if (find(single_row_coverings.begin(), single_row_coverings.end(), i) != single_row_coverings.end()) {
						/* single_row_coverings contains i */
						single_column_coverings.push_back(j);
					}
				}

				this->column_coverings_.push_back(single_column_coverings);
			}

			file.close();

			cout << "File is closed." << endl;
		}
		else {

			// TODO: throw exception
			cout << "Unable to open file" << endl;
		}

	}

};