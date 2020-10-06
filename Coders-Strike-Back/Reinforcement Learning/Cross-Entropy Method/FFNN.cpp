#include "FFNN.hpp"

float ReLU(float);



FFNN::FFNN() {
    shape.clear();
    weights.clear();
    biais.clear();
    layers = 0;
}

FFNN::FFNN(std::vector<int> s) {
    shape.clear();
    shape.push_back(s[0]);
    
    layers = (int)s.size();
    
    for (int i = 1; i < layers; i++)
        addLayer(shape[i]);
}

void FFNN::setParameters(std::vector<float> & theta) {
    int k = 0;
    
    for (int l = 1; l < layers; l++) {
        for (int i = 0; i < shape[l]; i++) {
            for (int j = 0; j < shape[l-1]; j++) {
                weights[l-1][i][j] = theta[k];
                k++;
            }
            biais[l-1][i] = theta[k];
            k++;
        }
    }
                
}

std::vector<float> FFNN::evaluate(std::vector<float> input) {
    std::vector<float> output;
    
    for (int l = 1; l < layers; l++) {
        output = std::vector<float>(shape[l], 0.f);
        
        for (int i = 0; i < shape[l]; i++) {
            for (int j = 0; j < shape[l-1]; j++)
                output[i] += weights[l-1][i][j] * input[j];
            output[i] = ReLU(output[i]);
        }
        
        input = output;
    }
    
    return output;
}

void FFNN::addLayer(int s) {
    int prevLayer = shape.back();
    shape.push_back(s);
    
    weights.push_back(Matrix(s, std::vector<float>(prevLayer, 0.f)));
    biais.push_back(std::vector<float>(s, 0.f));
}


float ReLU(float u) {
    if (u < 0.f)
        return 0.f;
    else
        return u;
}
