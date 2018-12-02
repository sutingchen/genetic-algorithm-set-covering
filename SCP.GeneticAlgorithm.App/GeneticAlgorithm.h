//#include <boost/algorithm/string.hpp>
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

using namespace std;

class GeneticAlgorithm {

private:
	//private member variables
	int t = 0;
	Problem problem;
	int population_size;
	vector<boost::dynamic_bitset<>> population; // all solutions
	vector<int> population_fitness;
	int running_time;
	int tournament_size;
	list<map<long, int>> log;

	// Private member functions
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

	void Evolve() {
		bool unique = false;
		boost::dynamic_bitset<> new_solution;
		while (!unique) {
			boost::dynamic_bitset<> parent_one = TournamentSelection();
			boost::dynamic_bitset<> parent_two = TournamentSelection();
			new_solution = Crossover(parent_one, parent_two);

		}
	}

public:
	// Constructor
	GeneticAlgorithm(int t, Problem problem, int population_size, int running_time, int tournament_size);

	// Public member functions
	void Initialize();



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

