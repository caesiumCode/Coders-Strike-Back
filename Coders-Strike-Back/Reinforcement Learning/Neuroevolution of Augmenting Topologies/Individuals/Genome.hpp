#ifndef Genome_hpp
#define Genome_hpp

#include <vector>

#include "Gene.hpp"

class Genome {
public:
    Genome();
    
    std::vector<float> evaluate(std::vector<float>);

    std::vector<Link> links;
    std::vector<Node> nodes;
    
    float score;
};

#endif /* Genome_hpp */
