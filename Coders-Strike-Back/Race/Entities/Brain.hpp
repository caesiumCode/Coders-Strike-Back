#ifndef Brain_hpp
#define Brain_hpp

#include <vector>

#include "Checkpoint.hpp"
#include "Move.hpp"

#include "Env.hpp"

#include "Genome.hpp"

class Brain {
public:
    Brain();
    
    void setGenome(Genome*);
    
    Move decision(const sf::Vector2f&, const sf::Vector2f&, float, const std::vector<Checkpoint>&, int);
    
    bool empty;
    
private:
    Genome* genome;
};

#endif /* Brain_hpp */
