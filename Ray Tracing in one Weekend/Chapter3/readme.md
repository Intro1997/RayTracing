&emsp;&emsp;本章实现了 ray 类，使用 ray 类和 vec3 类重新生成了一张蓝色渐变图。代码放在下面了。
ray 类
```c++
#ifndef Ray_H
#define Ray_H
#include "vec3.h"

class ray{
public:
    vec3 A;
    vec3 B;
    
    ray(){}
    ray(const vec3 &a, const vec3 &b) { A = a; B = b; }
    vec3 origin() const { return A; }
    vec3 direction() const { return B; }
    vec3 point_at_paramter(float t) const { return A + t*B; }

};
#endif
```
主程序代码：
```c++
vec3 color(const ray& r){
    vec3 unit_vec = unit_vector(r.direction());
    float t = 0.5 * (unit_vec.y() + 1.0);
    return (1-t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
    const char* path = "img/test.ppm";
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
    outFile << "P3\n" << nx << " " << ny << "\n255\n";
    for(int y = ny-1; y >= 0; --y){
        float v = float(y) / float(ny);
        
        for(float x = 0; x < nx; ++x){
            float u = float(x) / float(nx);
            ray r(origin, left_corner + u*horizon + v*vertical);
            vec3 col = color(r);
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
```