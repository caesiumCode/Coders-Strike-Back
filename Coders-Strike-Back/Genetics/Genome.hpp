#ifndef Genome_hpp
#define Genome_hpp

#include <vector>
#include "Gene.hpp"

class Genome {
public:
    Genome();

    std::vector<Gene> genes;
};

#endif /* Genome_hpp */
