#ifndef FFNN_hpp
#define FFNN_hpp

#include <vector>

typedef std::vector<std::vector<float>> Matrix;

// Feedforward Neural Network
class FFNN {
    FFNN();
    FFNN(std::vector<int>);
    
    void setParameters(std::vector<float>&);
    std::vector<float> evaluate(std::vector<float>);
    
    int layers;
    std::vector<int> shape;
    std::vector<Matrix> weights;
    Matrix biais;
    
private:
    void addLayer(int);
};

float ReLU(float);

#endif /* FFNN_hpp */
