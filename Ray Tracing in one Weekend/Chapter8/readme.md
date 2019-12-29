&emsp;&emsp;在本章，作者将前一章的 lambertian 材质抽象成一个 material 类。材质一般有两种情况，一种是 Lambertian（模糊材质），另一种是 Metal（金属材质）。前者无规律（任意的）散射光束，后者则类似于镜面反射。material 类包含一个纯虚函数 scatter 用来设定不同材质的反射情况。想象这个场景，光线击中物体，物体散射光线，追踪被散射的光线，直到没有击中物体。
&emsp;&emsp;仔细分析一下上述过程，光线击中物体，物体要做出散射行为，那么这个行为要根据物体本身的属性（材质）来划分，是 Lambertian 还是 Metal。被散射出去的光应该具有该物体本身的颜色（albedo）。根据这个分析，就可以确定 material 类与之前建立的类之间的关系了。
&emsp;&emsp;光线击中物体，这个行为被定义在 hitable 类中，由于击中之后，要判断物体的材质，因此需要定义一个记录材质的成员变量，因此作者在 hit_record 结构体中添加了 material *mat_ptr，碰撞发生时，更新这个成员变量，用来记录被光线碰撞的物体材质。这里直接使用 material 的原因后面会提到。接着根据材质需要实现相应的 scatter 方法。因此作者实现了 lambertian 和 metal 类，继承 material 类，并实现纯虚函数 scatter。由于光线撞击到物体后，需要散射，继续判断是否撞击到其他物体，因此需要递归实现，并且需要记录相应的碰撞信息，因此需要包含 hit_record 结构体。这样一来就会有矛盾。material 因为需要碰撞碰撞信息因此要包含 hit_record（在 hitable 类中），hitable 类需要包含 material 类来记录被光线碰撞的物体材质信息，实际上产生了一个环状包含结构，这个是不允许的。因此，作者在 hitable 类中，创建了一个类变量，并设置了类指针，指向对应的类，这样就解决了环状包含结构。
&emsp;&emsp;除了完全光滑的金属材质之外，现实中也可能会出现非完全光滑的金属，这个效果可以通过对计算好的镜面反射光线方向，做一次半径为 r 的随机方向选取，其中 r 决定模糊程度，作者限制在了 0.0 到 1.0，不过可以根据自己的喜好来调整，太大了感官上就与非金属类似了。
&emsp;&emsp;本章的代码依旧放进了 code 文件夹中。    