# dependencies

1. `sudo apt install libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev libxcursor-dev libxinerama-dev mesa-utils libxxf86vm-dev`
2. tutorial: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/
3. opengl 4.5 manual: https://registry.khronos.org/OpenGL-Refpages/gl4/html/
4. check opengl version on ubuntu (need mesa-utils): `glxinfo | grep "OpenGL version"`

# build && run tutorial01_first_window
1. `mkdir build && cd build`
2. `cmake ..`
3. `make tutorial01_first_window`
4. `./tutorial01_first_window`
