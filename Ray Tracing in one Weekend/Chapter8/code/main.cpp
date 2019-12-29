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
#include "material.h"


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


vec3 color(const ray& r, hitable_list *world, int depth){
    hit_record rec;    
    if(world->hit(r, 0.001, MAXFLOAT, rec)){
        ray scattered;
        vec3 attenuation;
        if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)){            
            return attenuation * color(scattered, world, depth + 1);
        }
        else{
            return vec3(0.0, 0.0, 0.0);
        }
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
    cout << "initialize spheres" << endl;
    hitable *list[4];
    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3));
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new metal(vec3(0.8, 0.8, 0.8), 5.0));
    hitable_list *world = new hitable_list(list, 4);
    cout << "initialize complete!" << endl << endl;
    
    clock_t start, end;
    start = clock();
    
    outFile << "P3\n" << nx << " " << ny << "\n255\n";
    for(int y = ny-1; y >= 0; --y){
        for(int x = 0; x < nx; ++x){
            vec3 col = vec3(0.0, 0.0, 0.0);
            for(int s = 0; s < ns; s++){
                float u = float(x + drand48()) / float(nx);
                float v = float(y + drand48()) / float(ny);                
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
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
