#include "Collision.hpp"


Collision::Collision() {
    type = -1;
    cp = nullptr;
    pods.clear();
    time = -1.f;
}

Collision::Collision(Checkpoint* a, Pod* b) {
    type = 0;
    cp = a;
    pods.clear();
    pods.push_back(b);
    time = -1.f;
}

Collision::Collision(Pod* a, Pod* b) {
    type = 1;
    cp = nullptr;
    pods.clear();
    pods.push_back(a);
    pods.push_back(b);
    time = -1.f;
}


Collision collide(Checkpoint& cp, Pod& pod) {
    Collision collision(&cp, &pod);
    collision.type = 0;
    
    float S = scal(cp.position - pod.position, -pod.speed);
    
    if (S < 0.f) {
        float vtemp = norm2(pod.speed);
        float delta = 4.f*(S*S - vtemp*(norm2(cp.position - pod.position) - cp.radius*cp.radius));
        
        if (delta > 0.f) {
            collision.time = (-2.f*S - sqrt(delta))/(2.f*vtemp);
        } else {
            collision.time = -1.f;
        }
    } else {
        collision.time = -1.f;
    }
    
    return collision;
}

Collision collide(Pod& pod1, Pod& pod2) {
    Collision collision(&pod1, &pod2);
    collision.type = 1;
    
    float S = scal(pod1.position - pod2.position, pod1.speed - pod2.speed);
    
    if (S < 0.f) {
        float vtemp = norm2(pod1.speed - pod2.speed);
        float delta = 4.f*(S*S - vtemp*(norm2(pod1.position - pod2.position) - (pod1.radius + pod2.radius)*(pod1.radius + pod2.radius)));
        
        if (delta > 0.f) {
            collision.time = (-2.f*S - sqrt(delta))/(2.f*vtemp);
        } else {
            collision.time = -1.f;
        }
    } else {
        collision.time = -1.f;
    }
    
    return collision;
}
