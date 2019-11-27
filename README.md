# Practical Assignment 5
**Name:** .......
## Problem 5.1 
### Reflection (Points 20)
In contrast to the rasterization algorithms, raytracing can simulate physically correct reflections and refractions. In this assignmnet we will extend the Phong shader to handle both reflections and refractions. 
Proceed as follows:
1. Fork the current repository.
2. Modify the README.md file in your fork and put your name (or names if you work in a group) above.
3. You will find the _torus knot_ model in your data folder.
4. Turn on BSP-support by enabling the flag `ENABLE_BSP` in types.h file or in cmake-gui.exe application.
5. Extend ```CShaderPhong::Shade()``` to also support reflections.
6. Test your implementation with torus knot.obj. 
If everything is correct your images should look like this:  
![](./doc/mirror.jpg) 

## Problem 5.2
### Refraction (Points 30)
In the last exercise you have learned that the appearence of a surface can be changed by using a modified _surface normal_. In this exercise we will implement a technique called _bump mapping_ which bumps the surface normal sideways such that a surface has the impression of beeing bumped. This often allows to generate the appearance of highly complex surface with only very few primitives. In order to do this, three parameters have to be known for each surface point:
1. The original surface normal _N_.
2. A local coordinate frame for this surface point. Though any coordinate frame can be used (as long as it is consistent), the usual way is to use the surface derivates in _u_ and _v_ direction, called _dPdu_ and _dPdv_.
3. The amount _delta_u_, _delta_v_ of deviation along these tangent vectors. The deviation is usually either read from a texture, or is computed procedurally. The final normal during shading (also for reflections) is then _N' = Normalized(N + delta_u * dPdu + delta_v * dPdv)_.  

In this exercise, you will implement a very basic version of this:
- As surface derivatives, use _dPdu = (1, 0, 0)_ and dPdv = _(0, 0, 1)_.
- For the amount of deviation, use a simple procedural approach, by computing _delta_u = 0.5 * cos(3 * H_x * sin(H_z))_, _delta_v = 0.5 * sin(13 * H_z)_. _H_ denotes the hit point of the ray with the surface.  

For your implementation, proceed as follows:
- Implement the Shade-method in ShaderPhongBumpMapped.h by first copying the ```Shade()```-method from the basic phong shader and then modifying the normal at the beginning of the ```Shade()``` function, following the guidlines given above.
If your shader work correct you should get an image like this using the scene description in main.cpp:  
![bump](./doc/bump_mapping.jpg)

**Tip:** The concept for a local coordinate frame will also be necessary for many other shading concepts, like _e.g._ procedural shading. For the exam, you will probably need such a concept, as the above hardcoded version will not be powerful enough.  
As getting the correct surface derivates can be somewhat complicated, there is also a simpler (though not as powerful) way of getting an orthonormal surface coordinate frame from the surface normal, which is similar to our way of generating the orthonormal camera coordinate frame from the camera direction. For a detailed discussion about surface derivatives you can also read Matt Pharr’s book _Physically Based Rendering_.

## Problem 5.3
### Glass Shading (Points 50)
Until now we have only used one color per object. Nevertheless, in reality, _e.g._ in games, objects are very often colorful because of the usage of textures. This is also a way of making a surface look more geometrically complex. Usually, textures are used by storing _texture coordinates_ at the vertices of each triangles, and interpolating those to find the correct texel that has to be used for a surface point.
1. Turn BSP-support on
2. In the framework is a new class ```CPrimTriangleSmoothTextured``` (derived from ```CPrimTriangleSmooth```), that additionally has the three fields ```Vec2f ta, tb, tc```, which correspond to the texture coordinates at vertex ```a```, ```b```, and ```c```, respectively. Here we will use ```Vec2f```’s to store the texture coordinates (not ```Vec3f```), because they require only 2 coordinates (barycentric coordinates). Add support for texture coordinates to your parser (```CScene::ParseOBJ()```).
3. Implemet the method ```Vec2f CPrimTriangleSmoothTextured::getUV(const Ray& ray) const``` which is now a virtual method in your primitive base class. In ```CPrimTriangleSmoothTextured```, implement this function to return the _x_ and _y_ coordinates of the interpolated vertex texture coordinates. (For other primitives, just ignore it for now, we’ll only use texture-shaders with triangles for now).
4. Implement the ```CShaderEyelightTextured::Shade()``` method to use the texture coordinates returned by ```getUV()``` and combine the texel color with the calculated eyelight color using the vector product. 

Test your implementation on barney.obj with barney.bmp. If everything is correct your image should look like this:
![barney](./doc/barney.jpg)
