#ifndef Population_hpp
#define Population_hpp

#include <vector>
#include "Genome.hpp"
#include "Species.hpp"

class Population {
public:
    Population();
    Population(int popId);

    std::vector<Genome> genomes;
    std::vector<Species> species;
    int id = 0;

    void simulate(int);
    void regroup();
    Population createNewGeneration();
};

#endif /* Population_hpp */
