#include <iostream>
using namespace std;
#include <fstream>
#include <cfloat>
#include <ctime>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "sphere.h"
#include "hitablelist.h"
#include "camera.h"

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

vec3 random_in_unit_sphere(){
    vec3 p;
    do{
    p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1.0, 1.0, 1.0);
    } while(p.square_length() >= 1.0);
    return p;
}

vec3 color(const ray& r, hitable_list *world){
    hit_record rec;    
    if(world->hit(r, 0.001, MAXFLOAT, rec)){
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * color(ray(rec.p, target - rec.p), world);
    }
    else{
        vec3 unit_vec = unit_vector(r.direction());
        float t = 0.5 * (unit_vec.y() + 1.0);
        return (1-t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main() {
    const char* path = "img/result.ppm";
    int nx = 200 , ny = 100, ns = 100;
    camera cam;
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
    clock_t start, end;
    start = clock();
    for(int y = ny-1; y >= 0; --y){
        for(int x = 0; x < nx; ++x){
            vec3 col = vec3(0.0, 0.0, 0.0);
            for(int s = 0; s < ns; s++){
                float u = float(x + drand48()) / float(nx);
                float v = float(y + drand48()) / float(ny);                
                ray r = cam.get_ray(u, v);
                col += color(r, world);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            rgb[0] = int(255 * col[0]);
            rgb[1] = int(255 * col[1]);
            rgb[2] = int(255 * col[2]);
            outFile << rgb << endl;
        }
    }
    outFile.close();
    end = clock();
    double endtime = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Finish in " << endtime << "s.\n" << endl;
    return 0;
}
