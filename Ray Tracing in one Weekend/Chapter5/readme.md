&emsp;&emsp;本章修改了之前能看到视角后方球体的情况，修改后的代码如下：
```c++
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

vec3 color(const ray& r){
    float t = hit_sphere(vec3(0.0, 0.0, -1.0), 0.5, r);
    if(t > 0.0){
        vec3 N = unit_vector(r.point_at_paramter(t) - vec3(0.0, 0.0, -1.0));
        return vec3(N.x()+1, N.y()+1, N.z()+1) * 0.5f;
    }
    vec3 unit_vec = unit_vector(r.direction());
    t = 0.5 * (unit_vec.y() + 1.0);
    return (1-t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}
```
之前的代码规定了光线的方向为 (-2.0, -1.0, -1.0) 和一段位移的和，但总体朝向负方向，而 $t$ 为正时，总体方向才为正，因此要求求根公式最后的结果为正。
&emsp;&emsp;作者接着实现了碰撞类（hitable.h），和碰撞列表类（hitablelist.h），碰撞类提供接口，供不同物体继承并实现对应的光线碰撞检测，并记录距离摄像机最近物体的距离，体现遮挡关系，记录了法向量，光线向量和参数 t。碰撞列表类 处理继承了 碰撞类 类对象与光线的碰撞检测以及遮挡关系，对应代码请在 code 文件夹中参阅。