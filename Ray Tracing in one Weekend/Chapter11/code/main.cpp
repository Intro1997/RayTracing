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

hitable *random_scene() {
    int n = 500;
    hitable **list = new hitable*[n+1];
    list[0] =  new sphere(vec3(0,-1000,0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = drand48();
            vec3 center(a+0.9*drand48(),0.2,b+0.9*drand48());
            if ((center-vec3(4,0.2,0)).length() > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    list[i++] = new sphere(center, 0.2,
                        new lambertian(vec3(drand48()*drand48(),
                                            drand48()*drand48(),
                                            drand48()*drand48())
                        )
                    );
                }
                else if (choose_mat < 0.95) { // metal
                    list[i++] = new sphere(center, 0.2,
                            new metal(vec3(0.5*(1 + drand48()),
                                           0.5*(1 + drand48()),
                                           0.5*(1 + drand48())),
                                      0.5*drand48()));
                }
                else {  // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

    return new hitable_list(list,i);
}


vec3 color(const ray& r, hitable *world, int depth){
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
    int nx = 2000 , ny = 1000, ns = 100;
    vec3 lookfrom(10, 1, 4);
    vec3 lookat(0, 0, -1);
    float dist_to_focus = (lookfrom - lookat).length();
    float aperture = 0.1;
    camera cam(lookfrom, lookat, vec3(0.0, 1.0, 0.0), 30.0, float(nx)/float(ny), aperture, dist_to_focus);
    vec3 rgb;
    
    ofstream outFile(path);
    
    if(outFile.fail()){
        cout << "Create file writing stream failed" << endl;
    }
    hitable *world = random_scene();
    
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
