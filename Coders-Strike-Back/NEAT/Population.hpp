#ifndef Population_hpp
#define Population_hpp

#include <vector>

#include "Genome.hpp"
#include "Species.hpp"

class Population {
public:
    Population();

    std::vector<Genome> genomes;
    std::vector<Species> species;

    void simulate(int);
    void regroup();
    Population nextGeneration();
};

#endif /* Population_hpp */
