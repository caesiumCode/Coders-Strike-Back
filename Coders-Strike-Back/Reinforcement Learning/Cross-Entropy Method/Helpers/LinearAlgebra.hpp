#ifndef LinearAlgebra_hpp
#define LinearAlgebra_hpp

#include <vector>

typedef std::vector<float> Vector;

class Matrix {
public:
    Matrix();
    Matrix(unsigned int, unsigned int);
    
    static Matrix identity(unsigned int);
    static Matrix zero(unsigned int);
    
    Vector& operator[](unsigned int);
    
    Vector operator*(const Vector &);
    
    void operator*=(float);

    
private:
    unsigned int height, width;
    std::vector<Vector> data;
};

Vector operator+(const Vector &, const Vector &);
float operator%(const Vector &, const Vector &);

#endif /* LinearAlgebra_hpp */
