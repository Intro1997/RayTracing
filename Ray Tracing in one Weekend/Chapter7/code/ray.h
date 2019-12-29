#ifndef Ray_H
#define Ray_H
#include "vec3.h"

class ray{
public:
    vec3 A;
    vec3 B;
    
    ray(){}
    ray(const vec3 &a, const vec3 &b) { A = a; B = b; }
    vec3 origin() const { return A; }
    vec3 direction() const { return B; }
    vec3 point_at_paramter(float t) const { return A + t*B; }

};
#endif
