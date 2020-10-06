#include "Population.hpp"

Population::Population() {
	genomes.clear();
    species.clear();
}

Population::Population(int s) : Population() {
    size = s;
    
    for (int i = 0; i < size; i++)
        genomes.push_back(Genome());
}

void Population::play(int) {

}

void Population::speciation() {
    
}

void Population::selection() {
    
}

void Population::mating() {
    
}

void Population::mutation() {
    
}
