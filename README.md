NinjaOctopushBurgersOfDoom
==========================

School project implementing various 3D techniques in OpenGL (C++11).

#Implemented Techniques
The mandatory techniques are perspective rendering, lighting, textures, three-dimensional objects and first-person camera movement.

Apart from these, we are also aiming to implement the following techniques (implemented|mandatory|available):

##Core (0|1|2)
* Deferred rendering and lighting. (TODO)

##Geometry (1|2|5)
* Height-map terrain rendering, user can walk on the terrain.

##Texturing and lighting (0|1|3)
* Blend-mapping. (TODO)

##Projection (0|1|4)

##Acceleration (1|2|3)
* Back-face culling using geometry shader.

##Miscellaneous (0|2|9)
* Particle system with billboarded particles. (TODO)

#Libraries
Uses OpenGL, [glew](http://glew.sourceforge.net/), [GLFW](http://www.glfw.org/), [OpenGL Mathematics](http://glm.g-truc.net/0.9.6/index.html), [simpleini](https://github.com/brofield/simpleini),  [stb](https://github.com/nothings/stb) and [OpenAL Soft](http://kcat.strangesoft.net/openal.html).

#License
This project is licensed under the MIT license.

glew is licensed under the Modified BSD License, the Mesa 3-D License, and the Khronos License. GLFW is licensed under the zlib/libpng license. OpenGL Mathematics is licensed under the Happy Bunny license. simpleini is licensed under the MIT license. stb is public domain. OpenAL Soft is licensed under the LGPL.

#Resources
The resources (textures, models, etc.) for this project are available separately and under a separate license (all rights reserved). You can download them [here](https://www.dropbox.com/sh/be6nx0qehx18kef/AABQPizx1kvYIurCqlS8N6uga?dl=1). Extract them to 3D Project/Resources.

#Contributing
Since this is a school project, our intention is to implement all of this ourselves. This means we won't accept pull requests from other people. You can naturally still fork the project and develop your own version if you want to.

##Guidelines
Class names are in PascalCase, methods and variables in camelCase. Classes should be implemented in their own header-files with accompanying .cpp-files. These files should have the same filename as the name of the class (with the same capitalization). Source files implementing other functionality should be named in camelCase.

'using namespace' in a header file is strictly forbidden; it's acceptable in .cpp-files.

GLSL shaders should be stored in shaderName_type.glsl files in Resources, where shaderName is the name of the shader (eg. "default") and type is the type of shader (eg. "fragment", "geometry" or "vertex"). Example: "default_vertex.glsl".

Use issue tracker to assign issues to person responsible for fixing them so multiple people don't work on the same thing.
