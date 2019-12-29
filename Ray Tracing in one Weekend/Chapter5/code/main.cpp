#include <iostream>
using namespace std;
#include <fstream>
#include <cfloat>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "sphere.h"
#include "hitablelist.h"

float hit_sphere(const vec3& center, float radius, const ray& r){
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    if(discriminant < 0){
        return -1.0;
    }
    else{
        return (-b - sqrt(discriminant)) / (2.0*a);
    }
}

vec3 color(const ray& r, hitable_list *world){
    hit_record rec;
    if(world->hit(r, 0.0, MAXFLOAT, rec)){
        return 0.5 * vec3(rec.normal.x()+1.0, rec.normal.y()+1.0, rec.normal.z()+1.0);
    }
    else{
        vec3 unit_vec = unit_vector(r.direction());
        float t = 0.5 * (unit_vec.y() + 1.0);
        return (1-t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main() {
    const char* path = "img/result.ppm";
    int nx = 200 , ny = 100;
    vec3 origin(0.0, 0.0, 0.0);
    vec3 left_corner(-2.0, -1.0, -1.0);
    vec3 horizon = vec3(4.0, 0.0, 0.0);
    vec3 vertical = vec3(0.0, 2.0, 0.0);
    vec3 rgb;
    
    ofstream outFile(path);
    if(outFile.fail()){
        cout << "Create file writing stream failed" << endl;
    }
    
    hitable *list[2];
    list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5);
    list[1] = new sphere(vec3(0.0, -100.5, -1.0), 100.0);
    hitable_list *world = new hitable_list(list, 2);
    
    outFile << "P3\n" << nx << " " << ny << "\n255\n";
    for(int y = ny-1; y >= 0; --y){
        float v = float(y) / float(ny);
        for(float x = 0; x < nx; ++x){
            float u = float(x) / float(nx);
            ray r(origin, left_corner + u*horizon + v*vertical);
            vec3 col = color(r, world);
            rgb[0] = int(255 * col[0]);
            rgb[1] = int(255 * col[1]);
            rgb[2] = int(255 * col[2]);
            outFile << rgb << endl;
        }
    }
    outFile.close();
    cout << "Finish\n" << endl;
    return 0;
}
