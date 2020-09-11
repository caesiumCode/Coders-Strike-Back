#ifndef Race_hpp
#define Race_hpp

#include <vector>
#include <cstdlib>
#include <ctime>

#include "Checkpoint.hpp"
#include "Pod.hpp"
#include "Geometry.hpp"
#include "ResourceFile.hpp"

class Race {
public:
    Race();
    Race(unsigned int);
    
    void reset();
        
    // Constant variables
    static const int WIDTH = 16000, HEIGHT = 9000;
    const int CHECKPOINT_MIN = 2, CHECKPOINT_MAX = 6;
    const int CHECKPOINT_RADIUS = 600, POD_RADIUS = 400;
    const int ANGLE_LIMIT = 18, THRUST_LIMIT = 100, TURN_LIMIT = 100;
    const float FRICTION_COEFFICIENT = 0.85f;
    const sf::Color CHECKPOINT_COLOR = sf::Color::White, TEAM1_COLOR = sf::Color::Blue, TEAM2_COLOR = sf::Color::Red;
    
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
