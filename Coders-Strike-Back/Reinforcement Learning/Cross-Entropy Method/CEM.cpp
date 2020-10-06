#include "CEM.hpp"

CEM::CEM() {
    
}

CEM::CEM(int d, int s) {
    dim = d;
    sampleSize = s;
    
    mean = std::vector<float>(dim, 0.f);
}
