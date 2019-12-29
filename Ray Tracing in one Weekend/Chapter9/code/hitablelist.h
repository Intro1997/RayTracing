//
//  hitablelisth.h
//  RayTracing
//
//  Created by Outro on 2019/12/24.
//  Copyright © 2019 Outro. All rights reserved.
//

#ifndef hitablelist_h
#define hitablelist_h

#include "hitable.h"

class hitable_list : public hitable{
public:
    hitable **list;
    int list_size;    
    
    hitable_list(){}
    hitable_list(hitable ** l, int n){ list = l; list_size = n; }
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record &record) const;
};

bool hitable_list::hit(const ray &r, float t_min, float t_max, hit_record &record) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double cloest_so_far = t_max;
    for(int i = 0; i < list_size; i++){
        if(list[i]->hit(r, t_min, cloest_so_far, temp_rec)){
            hit_anything = true;
            cloest_so_far = temp_rec.t;
            record = temp_rec;
        }
    }
    return hit_anything;        
}

#endif /* hitablelisth_h */
