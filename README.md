Rapid Visualization and GUI Toolkit: "RGUI"
==============================================


Easy 2D drawing interface accelerated by OpenGL
Simple GUI widgets


## Example use cases:
- Interactive visualization and art
- Simple game engine
- Quick GUIs


[![Build Status](https://travis-ci.com/russellsch/RGUI.svg?token=roZd6USoNAjScqsNVXzw&branch=master)](https://travis-ci.com/russellsch/RGUI)


## Changelog

### v3.0.0

- [X] Change build system to CMake
- [X] Change primary target to Linux/Ubuntu
- [ ] Remove old Windows code
- [X] Upgrade to SDL2
- [X] Upgrade Freetype
- [X] Upgrade OpenGL 3.1
- [X] Basic UI widget functionality working on Linux
- [X] Simplified import for use to single h file
- [X] Refactored RGB color class to be more C++11 friendly
- [X] Upgrade enums to enum classes so they are scoped
- [X] Fixed bug preventing mouse drag code from working
- [X] Change RGObject mouse delegation handling to use enums for clarity
- [X] Add GPLv3 license
- [X] Remove inheritance of RGObj on RGRect in favor of composition approach
- [X] Travis.ci continuous integration working

- [ ] Basic UI demo of working UI widgets


- [ ] Change timer code to use std::chrono
- [ ] Rename all private variables to start with '_'

- [ ] Upgrade font renderer to support multiple sizes for one font

- [ ] Update scenegraph to manage and render RGDraw calls to textures

- [ ] Add CMake library exports
- [ ] Add Dockerfile
- [ ] Add better UTF-8 font rendering demo
- [ ] Change to namespace RG and drop RG prefix on class names


- [ ] Mousewheel events and delegation


### v4.0.0 (FUTURE)

- [ ] Switch to entity-component-system architecture
- [ ] Upgrade RGDraw to use GLSL shaders
- [ ] Upgrade RGDraw for curves, joined lines, proper line end caps, etc.