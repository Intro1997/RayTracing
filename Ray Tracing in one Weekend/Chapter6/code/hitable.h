//
//  hitable.h
//  RayTracing
//
//  Created by Outro on 2019/12/23.
//  Copyright © 2019 Outro. All rights reserved.
//

#ifndef hitable_h
#define hitable_h

#include "ray.h"

struct hit_record{
    float t;
    vec3 p;
    vec3 normal;
};

class hitable{
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& record) const = 0;
};

#endif /* hitable_h */
