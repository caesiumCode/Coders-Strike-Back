#include "Population.hpp"

Population::Population() {
	id = 0;
	genomes.clear();
}

Population::Population(int popId) {
	id = popId;
	genomes.clear();
}

void Population::simulate(int) {

}

void Population::regroup() {

}

Population Population::createNewGeneration() {
	return Population();
}