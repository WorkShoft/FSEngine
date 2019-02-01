# FSEngine

The FSEngine is a lightweight 2D game engine written in C++, it is still a work in progress however.

## Building

The project uses [premake5](https://premake.github.io/download.html) to generate makefiles, simply run ```premake5 gmake2``` on linux and ```premake5.exe vs2017``` on windows. I'd like to think you know what to do from here...

If you are insane enough to build this for your own project, the following libraries are required:

* [SDL2](https://github.com/garyservin/sdl2)
* [GLEW](https://github.com/nigels-com/glew) **NOTE: Build from source as the binarys provided by most linux software repos are out of date and do not support extensions used by this project**
* [pugixml](https://github.com/zeux/pugixml)
* [GLM](https://github.com/g-truc/glm)
* [STB (Image)](https://github.com/nothings/stb/blob/master/stb_image.h)
* [SPDLog](https://github.com/gabime/spdlog)
