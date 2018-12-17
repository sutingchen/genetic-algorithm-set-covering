#pragma once
#include <boost/dynamic_bitset.hpp>
#include <stdlib.h>
#include <random>
#include <vector>
#include <iostream>
#include <string>
#include <list>
#include <map>
#include "Problem.h"
#include "Solution.h"

#include <stdio.h>
#include <time.h>


using namespace std;

class GeneticAlgorithm {

private:
	//private member variables
	int t = 0;
	Problem problem;
	int population_size;
	vector<boost::dynamic_bitset<>> population; // all solutions
	vector<int> population_fitness;
	int running_time; // maximum running time
	int tournament_size;
	vector<pair<long, int>> log;

#pragma region private member functions
	boost::dynamic_bitset<> TournamentSelection() {
		int best_fitness = INT_MAX;
		boost::dynamic_bitset<> best;
		for (int i = 0; i < this->tournament_size; i++) {

			int random_number = rand() % this->population.size();
			boost::dynamic_bitset<> individual = population[random_number];
			if (best.empty() || this->population_fitness[random_number] < best_fitness) {
				best = individual;
				best_fitness = this->population_fitness[random_number];
			}
		}

		return best;
	}

	boost::dynamic_bitset<> Crossover(boost::dynamic_bitset<> parent_one, boost::dynamic_bitset<> parent_two) {
		boost::dynamic_bitset<> new_solution(parent_one.size());
		for (int i = 0; i < parent_one.size(); i++) {
			if (parent_one[i] == parent_two[i]) {
				new_solution.set(i, parent_one[i]);
			}
			else {
				double probability = Fitness(parent_one) / Fitness(parent_one) + Fitness(parent_two);
				double random_double = GenerateRandomDouble();
				if (random_double >= probability) {
					new_solution.set(i, parent_one[i]);
				}
				else {
					new_solution.set(i, parent_two[i]);
				}
			}
		}

		return new_solution;
	}

	boost::dynamic_bitset<> Mutation(boost::dynamic_bitset<> solution) {
		int random_integer = GenerateRandomInteger(solution.size());
		solution.flip(random_integer);

		return solution;
	}

	double GenerateRandomDouble() {
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_real_distribution<> dis(0, 1.0);

		return dis(gen);
	}

	int GenerateRandomInteger(int max) {
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_int_distribution<> dis(1, max);

		return dis(gen);
	}

	bool IsUnique(boost::dynamic_bitset<> solution) {

		for (int i = 0; i < this->population_size; i++) {
			boost::dynamic_bitset<> copy = solution;
			copy ^= this->population[i];
			if (copy.size()) {
				return false;
			}
			return true;
		}
	}

	bool IsConverged() {
		// std::map<long, int>::iterator it;


		if (this->log.empty() || this->log.size() < 60) {
			return false;
		}
		int best_fitness = this->log[log.size() - 1].second;
		for (int i = 1; i < 60; i++) {
			int temp = this->log[log.size() - 1].second;
			if (temp != best_fitness) {
				return false;
			}
		}
		return true;
	}

	int Fitness(boost::dynamic_bitset<> solution) {
		int fitness = 0;
		for (int i = 0; i < solution.size(); i++) {
			if (solution[i]) {
				fitness += problem.costs()[i];
			}
		}
		return fitness;
	}

	void GenerateInitialPopulation() {
		for (int i = 0; i < this->population_size; i++) {
			boost::dynamic_bitset<> solution = Solution::CreateSolution(this->problem);
			population.push_back(solution);
		}
	}

	void CalculateAllFitness() {
		for (int i = 0; i < this->population_size; i++) {
			population_fitness.push_back(Fitness(this->population[i]));
		}
	}

	boost::dynamic_bitset<> MakeFeasible(boost::dynamic_bitset<> solution) {
		return Solution::MakeFeasible(solution, problem);
	}

	void Evolve() {
		bool unique = false;
		boost::dynamic_bitset<> new_solution;
		while (!unique) {
			boost::dynamic_bitset<> parent_one = TournamentSelection();
			boost::dynamic_bitset<> parent_two = TournamentSelection();
			new_solution = Crossover(parent_one, parent_two);
			new_solution = Mutation(new_solution);
			new_solution = MakeFeasible(new_solution);
			unique = IsUnique(new_solution);

		}
		Replace(new_solution);
		cout << "New solution: " << new_solution;
		this->t++;
	}

	void Replace(boost::dynamic_bitset<> solution) {
		int average_fitness = 0;
		for (int i = 0; i < this->population_fitness.size(); i++) {
			average_fitness += this->population_fitness[i];
		}
		average_fitness = (int)average_fitness / this->population_fitness.size();

		bool is_replaced = false;

		while (!is_replaced) {
			int random_number = GenerateRandomInteger(this->population_fitness.size());
			if (this->population_fitness[random_number] > average_fitness) {
				this->population[random_number] = solution;
				this->population_fitness[random_number] = Fitness(solution);
				is_replaced = true;
			}
		}
	}

#pragma endregion

public:
	// Constructor
	GeneticAlgorithm(int t, Problem problem, int population_size, int running_time, int tournament_size);

	// Public member functions
	void Initialize();
	int GetBestFitness();
	void Train();
	vector<pair<long, int>> GetLog();

};

// constructor
GeneticAlgorithm::GeneticAlgorithm(int t, Problem problem, int population_size, int running_time, int tournament_size) {
	this->problem = problem;
	this->population_size = population_size;
	this->running_time = running_time;
	this->tournament_size = tournament_size;
}

void GeneticAlgorithm::Initialize() {
	GenerateInitialPopulation();
	CalculateAllFitness();
}

int GeneticAlgorithm::GetBestFitness() {
	int best_fitness = INT_MAX;
	for (int i = 0; i < this->population_size; i++) {
		if (this->population_fitness[i] < best_fitness) {
			best_fitness = this->population_fitness[i];
		}
	}
	return best_fitness;
}

vector<pair<long, int>> GeneticAlgorithm::GetLog() {
	return log;
}

void GeneticAlgorithm::Train() {

	/*double time_counter = 0;
	clock_t start_time = clock();

	while (!IsConverged() && ((clock() - start_time)/1000/60 < this->running_time)) {
		if (clock() - start_time % 1000 == 0) {
			log.push_back(make_pair(clock() - start_time, GetBestFitness()));
		}
		Evolve();
	}*/

	Evolve();

}

