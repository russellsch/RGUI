Rapid Visualization and GUI Toolkit: "RGUI"
==============================================


Easy 2D drawing interface accelerated by OpenGL
Simple GUI widgets


## Example use cases:
- Interactive visualization and art
- Simple game engine
- Quick GUIs





## Changelog

### v3.0.0
- [X] Change build system to CMake
- [X] Change primary target to Linux/Ubuntu
- [-] Remove old Windows code
- [X] Upgrade to SDL2
- [X] Upgrade Freetype
- [X] Upgrade OpenGL library version
- [X] Basic UI widget functionality working on Linux
- [X] Simplified import for use to single h file
- [X] Refactored RGB color class to be more C++11 friendly
- [X] Upgrade to OpenGL 3.1
- [X] Upgrade enums to enum classes so they are scoped
- [X] Fixed issues preventing drag code from working
- [-] Change RGObject mouse delegation handling to use enums for clarity

- [ ] Create basic UI demo of working UI widgets



- [ ] Upgrade font renderer to support multiple sizes for one font
- [ ] Add GPL license
- [ ] Add CMake library exports
- [ ] Add Dockerfile
- [ ] Add better UTF-8 font rendering demo
- [ ] Change to namespace RG and drop RG prefix on class names



### v4.0.0 (FUTURE)

- [ ] Switch to entity-component-system architecture
- [ ] Upgrade RGDraw to use GLSL shaders
- [ ] Upgrade RGDraw for curves, joined lines, proper line end caps, etc.