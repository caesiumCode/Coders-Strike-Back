#ifndef Species_hpp
#define Species_hpp

#include <vector>
#include "Genome.hpp"

class Species {
public:
    Species();

    std::vector<Genome> genomes;

    void sort();
    void reproduction();
};

#endif /* Species_hpp */
