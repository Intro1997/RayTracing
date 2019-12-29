//
//  camera.h
//  RayTracing
//
//  Created by Outro on 2019/12/25.
//  Copyright © 2019 Outro. All rights reserved.
//

#ifndef camera_h
#define camera_h

#include "vec3.h"
#include "ray.h"

class camera{
public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizon;
    vec3 vertical;
    
    camera(){
        lower_left_corner = vec3(-2.0, -1.0, -1.0);
        horizon = vec3(4.0, 0.0, 0.0);
        vertical = vec3(0.0, 2.0, 0.0);
        origin = vec3(0.0, 0.0, 0.0);
    }
    
    ray get_ray(float u, float v){
        return ray(origin, lower_left_corner + u * horizon + v * vertical);
    }
};

#endif /* camera_h */
