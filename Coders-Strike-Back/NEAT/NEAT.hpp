#ifndef NEAT_hpp
#define NEAT_hpp

#include "Population.hpp"

class NEAT {
public:
    NEAT();
    
    void evolve(int);
    
    int generation;
    Population population;
};

#endif /* NEAT_hpp */
