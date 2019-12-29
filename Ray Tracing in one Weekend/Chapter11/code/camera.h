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

vec3 random_in_unit_disk(){
    vec3 p;
    do{
        p = 2.0 * vec3(drand48(), drand48(), 0.0) - vec3(1.0, 1.0, 0.0);
    } while(dot(p, p) >= 1.0);
    return p;
}

class camera{
public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizon;
    vec3 vertical;
    float len_radius;
    vec3 w, u, v;

    camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist){
        float theta = vfov * M_PI / 180;
        float half_height = tan(theta / 2);
        float half_width = half_height * aspect;
        len_radius = aperture / 2;
        
        origin = lookfrom;
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);
        
        lower_left_corner = origin - half_height * v * focus_dist - half_width * u * focus_dist - w * focus_dist;
        horizon = half_width * 2 * u * focus_dist;
        vertical = half_height * 2 * v * focus_dist;
    }

    ray get_ray(float s, float t){
        vec3 rd = len_radius * random_in_unit_disk();
        vec3 offset = rd.x() * u + rd.y() * v;
        return ray(origin + offset, lower_left_corner + s * horizon + t * vertical - origin - offset);
    }
};



#endif /* camera_h */
