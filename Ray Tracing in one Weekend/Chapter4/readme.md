&emsp;&emsp;作者在本章视野范围内渲染了一个球（仅 2d），大致步骤如下：
1. 球心在 (0.0, 0.0, 0.0) 的方程为 $x^2 + y^2 + z^2 = R^2$
2. 球心在 (cx, cy, cz) 的方程为 $(x-cx)^2 + (y-cy)^2 + (z-cz)^2 = R^2$
3. 将 $x,y,z,cx,cy,cz$ 分别看作两个向量在坐标轴上的分量：$p(x,y,z),\ C(xc,yc,zc)$
4. 上一章提到过 $p(t) = A + t*B$ $A$ 为原点向量，$B$ 为方向向量，$t$ 为大小，则球方程可写成 $(p(t)-C)^2 = R^2$，整理可得：$(A+t*B-C)^2-R^2=0$
5. 进一步整理可得 $B^2*t^2 + 2(A-C)B*t + (A-C)^2 - R^2 = 0$，其中向量乘法均为点乘。
6. 由于 $(p(t)-C)$ 是 $C$ 到某个点 $p(t)$ 的向量，因此上述方程的未知数只有 $t$。
7. 二次函数有无根以及根的数量可以通过 $b^2-4ac$ 求出，这里不赘述。

据此可以实现函数：
```C++
bool hit_sphere(const vec3& center, float radius, const ray& r){
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

vec3 color(const ray& r){
    if(hit_sphere(vec3(0.0, 0.0, -1.0), 0.5, r))
        return vec3(1.0, 0.0, 0.0);
    vec3 unit_vec = unit_vector(r.direction());
    float t = 0.5 * (unit_vec.y() + 1.0);
    return (1-t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}
```
在函数 hit_sphere() 中，若 center 为 (0.0, 0.0, 1.0)，最终结果不会收到影响。这是因为 ```dot(oc, r.direction()``` 的几何意义为两向量夹角的余弦值，而 center 为 (0.0, 0.0, 1.0) 时，b 与原先的 b 正好相反，但是在 ```float discriminant = b*b - 4*a*c;``` 中，b 取了平方，因此最终结果与原先相同。作者在下一章会修改这里的 bug。