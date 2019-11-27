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
Now we need to extend ```CShaderPhong::Shade()``` to also support refractions.
Test your implementation with torus knot.obj and refraction coefficient k = 1.5 (glass) or k = 2.4 (diamond)
If everything is correct your images should look like this:  
![](./doc/glass.jpg) 

## Problem 5.3
### Glass Shading (Points 50)
Until now we have only used one color per object. Nevertheless, in reality, _e.g._ in games, objects are very often colorful because of the usage of textures. This is also a way of making a surface look more geometrically complex. Usually, textures are used by storing _texture coordinates_ at the vertices of each triangles, and interpolating those to find the correct texel that has to be used for a surface point.
1. Turn BSP-support on
2. In the framework is a new class ```CPrimTriangleSmoothTextured``` (derived from ```CPrimTriangleSmooth```), that additionally has the three fields ```Vec2f ta, tb, tc```, which correspond to the texture coordinates at vertex ```a```, ```b```, and ```c```, respectively. Here we will use ```Vec2f```’s to store the texture coordinates (not ```Vec3f```), because they require only 2 coordinates (barycentric coordinates). Add support for texture coordinates to your parser (```CScene::ParseOBJ()```).
3. Implemet the method ```Vec2f CPrimTriangleSmoothTextured::getUV(const Ray& ray) const``` which is now a virtual method in your primitive base class. In ```CPrimTriangleSmoothTextured```, implement this function to return the _x_ and _y_ coordinates of the interpolated vertex texture coordinates. (For other primitives, just ignore it for now, we’ll only use texture-shaders with triangles for now).
4. Implement the ```CShaderEyelightTextured::Shade()``` method to use the texture coordinates returned by ```getUV()``` and combine the texel color with the calculated eyelight color using the vector product. 

Test your implementation on barney.obj with barney.bmp. If everything is correct your image should look like this:
![barney](./doc/barney.jpg)
