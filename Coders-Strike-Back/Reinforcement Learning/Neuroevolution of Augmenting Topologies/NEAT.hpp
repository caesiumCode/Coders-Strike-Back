#ifndef NEAT_hpp
#define NEAT_hpp

#include "Population.hpp"

class NEAT {
public:
    NEAT();
    NEAT(int);
    
    void evolve(int);
    
    int generation;
    Population population;
    std::vector<float> scoreHistory;
};

#endif /* NEAT_hpp */
