#include "Race.hpp"

Race::Race() {
    team1 = {Pod(), Pod()};
    team2 = {Pod(), Pod()};
    
    laps = 0;
    checkpoints.clear();
    
    lapsDone = 0;
}
