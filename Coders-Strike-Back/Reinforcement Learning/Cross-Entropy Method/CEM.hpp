#ifndef CEM_hpp
#define CEM_hpp

#include <random>

#include "LinearAlgebra.hpp"

class CEM {
public:
    CEM();
    CEM(int, int);
    
    int dim, sampleSize;
    Vector mean;
    Matrix cov;
    
private:
    std::default_random_engine generator;
    std::normal_distribution<float> distribution;
};

#endif /* CEM_hpp */
