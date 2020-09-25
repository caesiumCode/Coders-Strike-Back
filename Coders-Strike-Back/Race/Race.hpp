#ifndef Race_hpp
#define Race_hpp

#include <vector>
#include <cstdlib>
#include <ctime>

#include "Checkpoint.hpp"
#include "Pod.hpp"
#include "Geometry.hpp"
#include "ResourceFile.hpp"

#include "Env.hpp"

class Race {
public:
    Race();
    Race(unsigned int);
    
    void reset();
    void reset(unsigned int);
    void update();
        
    // Players
    std::vector<Pod> team1, team2;
    int team1Size, team2Size;
    
    // Race path
    int laps;
    std::vector<Checkpoint> checkpoints;
    
    // Current race state
    int lapsDone, turnsDone;
    
private:
    unsigned int seed;
};

#endif /* Race_hpp */
