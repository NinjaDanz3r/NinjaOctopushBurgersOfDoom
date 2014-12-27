NinjaOctopushBurgersOfDoom
==========================

School project implementing various 3D techniques in OpenGL (C++).

#Implemented Techniques
The mandatory techniques are perspective rendering, lighting, textures, three-dimensional objects and first-person camera movement.

Apart from these, we are also aiming to implement the following techniques:

##Core

##Geometry
* Height-map terrain rendering, user can walk on the terrain. (TODO)

##Texturing and lighting
* Blend-mapping. (TODO)

##Projection

##Acceleration
* Back-face culling using geometry shader. (TODO)

##Miscellaneous

#Libraries
Uses OpenGL, [glew](http://glew.sourceforge.net/), [GLFW](http://www.glfw.org/) and [OpenGL Mathematics](http://glm.g-truc.net/0.9.6/index.html).

#License
This project is licensed under the MIT license.

glew is licensed under the Modified BSD License, the Mesa 3-D License, and the Khronos License. GLFW is licensed under the zlib/libpng license. OpenGL Mathematics is licensed under the Happy Bunny license.

#Contributing

Since this is a school project, our intention is to implement all of this ourselves. This means we won't accept pull requests from other people. You can naturally still fork the project and develop your own version if you want to.

##Guidelines

Class names are in PascalCase, methods and variables in camelCase. Classes should be implemented in their own header-files with accompanying .cpp-files. These files should have the same filename as the name of the class (with the same capitalization). Source files implementing other functionality should be named in camelCase.

'using namespace' in a header file is strictly forbidden; it's acceptable in .cpp-files.

GLSL shaders should be stored in shaderName_type.glsl files in Resources, where shaderName is the name of the shader (eg. "default") and type is the type of shader (eg. "fragment", "geometry" or "vertex"). Example: "default_vertex.glsl".

Use issue tracker to assign issues to person responsible for fixing them so multiple people don't work on the same thing.
