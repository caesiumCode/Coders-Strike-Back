#include "Genome.hpp"

Genome::Genome() {
	links.clear();
    nodes.clear();
    
    score = 0.f;
    
    /* - - - Nodes - - - */
    int id = 1;
    
    // Input nodes
    for (int i = 1; i <= 9; i++) {
        nodes.push_back(Node('I', id));
        id++;
    }
    
    // Output nodes
    for (int i = 1; i <= 5; i++) {
        nodes.push_back(Node('O', id));
        id++;
    }
}

std::vector<float> Genome::evaluate(std::vector<float> input) {
    return {};
}
