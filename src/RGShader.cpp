#include "rgui/RGShader.hpp"

namespace fs = std::experimental::filesystem::v1;       //Using experimental C++17 feature


RGShader::RGShader(std::string vertexFile, std::string fragmentFile) {
    std::string basePath = "shaders/";

    std::string vertexPath = fs::current_path().string() + basePath + vertexFile;
    std::string fragmentPath = fs::current_path().string() + basePath + fragmentFile;



    std::ifstream vertexStream(vertexPath);
    std::ifstream fragmentStream(fragmentPath);

    std::stringstream bufferVertex;
    std::stringstream bufferFragment;
    bufferVertex << vertexStream.rdbuf();
    bufferFragment << vertexStream.rdbuf();

    std::string vertexCode = bufferVertex.str();
    std::string fragmentCode = bufferFragment.str();


    program = glCreateProgram();
    if(program == 0) {
        std::cout << "glCreateProgram failed\n";
    } else {
        std::cout << "Shader program created with id: " << program << "\n";
    }

}


RGShader::~RGShader() {

    // TODO: remove each shader

    glDeleteProgram(program);
}
