#ifndef RGUI_RGSHADER_HPP
#define RGUI_RGSHADER_HPP


#include <GL/glew.h>
#include <SDL_opengl.h>


#include <iostream>
#include <fstream>
#include <experimental/filesystem>


class RGShader {


public:
    GLuint program;

    RGShader(std::string vertexFile, std::string fragmentFile);
    ~RGShader();
};


#endif //RGUI_RGSHADER_HPP
