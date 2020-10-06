#include "LinearAlgebra.hpp"

Matrix::Matrix() {
    data.clear();
}

Matrix::Matrix(unsigned int w, unsigned int h) {
    height = h;
    width = w;
    
    data = std::vector<std::vector<float>>(height, std::vector<float>(width, 0.f));
}

Matrix Matrix::identity(unsigned int dim) {
    Matrix M(dim, dim);
    
    for (int i = 0; i < dim; i++)
        M.data[i][i] = 1.f;
    
    return M;
}

Matrix Matrix::zero(unsigned int dim) {
    return Matrix(dim, dim);
}

std::vector<float>& Matrix::operator[](unsigned int h) {
    return data[h];
}

std::vector<float> Matrix::operator*(const std::vector<float> & u) {
    std::vector<float> v(width, 0.f);
    
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            v[i] += data[i][j] * u[j];
    
    return v;
}

void Matrix::operator*=(float a) {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            data[i][j] *= a;
}



Vector operator+(const Vector & u, const Vector & v) {
    Vector w;
    
    for (int i = 0; i < u.size(); i++)
        w[i] = u[i] + v[i];
    
    return w;
}

float operator%(const Vector & u, const Vector & v) {
    float scal = 0.f;
    
    for (int i = 0; i < u.size(); i++)
        scal += u[i] * v[i];
    
    return scal;
}
