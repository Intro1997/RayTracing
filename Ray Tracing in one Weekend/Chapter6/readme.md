&emsp;&emsp;作者在本章将 camera 抽象成 camera 类，代码如下：
```c++
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
```
除此之外，由于之前的球体边缘锯齿感很强，因此作者在这里做了一下抗锯齿的处理。处理方法是在一个像素范围内，做 100 次随机的，在（0, 1）范围内的偏移，将这些颜色加起来，取平均值进行抗锯齿处理。所有代码请参阅 code。