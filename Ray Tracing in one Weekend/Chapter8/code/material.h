//
//  material.h
//  RayTracing
//
//  Created by Outro on 2019/12/25.
//  Copyright © 2019 Outro. All rights reserved.
//

#ifndef material_h
#define material_h

#include "hitable.h"

vec3 random_in_unit_sphere(){
    vec3 p;
    do{
    p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1.0, 1.0, 1.0);
    } while(p.square_length() >= 1.0);
    return p;
}

vec3 reflect(const vec3 &v, const vec3 &n){
    return v - 2 * dot(v, n) * n;
}


class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

class lambertian : public material{
public:
    vec3 albedo;
    
    lambertian(const vec3 & a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }
    
};

class metal : public material {
public:
    vec3 albedo;
    float fuzz;
    
    metal(const vec3 & a, float f) : albedo(a) {
        if(f < 1.0)
            fuzz = f;
        else
            fuzz = 1.0;
    }
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);            
    }
};


#endif /* material_h */
