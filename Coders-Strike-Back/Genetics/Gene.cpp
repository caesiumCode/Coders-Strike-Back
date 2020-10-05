#include "Gene.hpp"

Gene::Gene() {
    activated = false;
    parameter = 0.f;
}

Gene::Gene(bool activation, float param) {
    activated = activation;
    parameter = param;
}

