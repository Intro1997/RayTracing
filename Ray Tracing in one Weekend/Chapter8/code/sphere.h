//
//  sphere.h
//  RayTracing
//
//  Created by Outro on 2019/12/23.
//  Copyright © 2019 Outro. All rights reserved.
//

#ifndef sphere_h
#define sphere_h

#include "vec3.h"
#include "hitable.h"

class sphere : public hitable{
public:
    float radius;
    vec3 center;
    material *mat_ptr;
    
    sphere(){}
    sphere(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m){}
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& record) const;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& record) const {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if(discriminant > 0){
        
        float temp = (-b - sqrt(discriminant)) / a;
        if(temp > t_min && temp < t_max){
            record.t = temp;
            record.p = r.point_at_paramter(temp);
            record.normal = (record.p - center) / radius;
            record.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if(temp > t_min && temp < t_max){
            record.t = temp;
            record.p = r.point_at_paramter(temp);
            record.normal = (record.p - center) / radius;
            record.mat_ptr = mat_ptr;
            return true;
        }
    }    
    return false;
}

#endif /* sphere_h */
