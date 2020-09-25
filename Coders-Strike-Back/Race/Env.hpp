#ifndef Env_hpp
#define Env_hpp

#define _USE_MATH_DEFINES
#include <math.h>

#include <SFML/Graphics.hpp>

class RACE {
public:
    static const int WIDTH = 16000, HEIGHT = 9000;
    static const int CHECKPOINT_MIN = 2, CHECKPOINT_MAX = 6;
};

class POD {
public:
    static const int RADIUS = 400;
    static constexpr float ANGLE_LIMIT = 18.f * M_PI / 180.f, FRICTION_COEFFICIENT = 0.85f;
    static const int THRUST_LIMIT = 100, TURN_LIMIT = 100;
};

class CP {
public:
    static const int RADIUS = 600;
};

#endif /* Env_hpp */
