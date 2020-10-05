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

    void play(int);
    void speciation();
    void selection();
    void mating();
    void mutation();
};

#endif /* Population_hpp */
