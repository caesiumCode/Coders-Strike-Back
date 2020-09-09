#ifndef Race_hpp
#define Race_hpp

#include <vector>

#include "Checkpoint.hpp"
#include "Pod.hpp"

class Race {
public:
    Race();
    
    // Players
    std::vector<Pod> team1, team2;
    
    // Race path
    int laps;
    std::vector<Checkpoint> checkpoints;
    
    // Current race state
    int lapsDone;
    
};

#endif /* Race_hpp */
