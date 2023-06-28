// "Copyright [2023] <Krzysztof Rudnicki>"
#ifndef ENGINE_ENGINE_DRAW_HPP_
#define ENGINE_ENGINE_DRAW_HPP_
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

#include "./constants.hpp"
#include "./textures.hpp"
#include "./renderLoop.hpp"

struct offsetsStruct {
  offsetsStruct() : xOffset(0), yOffset(0), zOffset(0) {}
  float xOffset, yOffset, zOffset;
};

struct drawFigureReturn {
  drawFigureReturn() : success(-1), VAO(0), VBO(0), EBO(0) {}
  int success;
  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;
};



drawFigureReturn drawFigure(const drawInput drawData);

void updateUniformColor(const Shader shaderProgram,
                        const std::string uniformName);

drawFigureReturn draw(
    const char* vertexPath = constants::VERTEX_SHADER_SOURCE_FILENAME,
    const char* fragmentPath = constants::FRAGMENT_SHADER_SOURCE_FILENAME,
    const float vertices[] = constants::TRIANGLE_VERTICES,
    const size_t verticesSize = constants::TRIANGLE_VERTICES_SIZE,
    const unsigned int indices[] = constants::TRIANGLE_INDICES,
    const size_t indicesSize = constants::TRIANGLE_INDICES_SIZE,
    const bool colorIncluded = false,
    const bool textureIncluded = false,
    std::vector<textureArgument> textureInfo = {},
    const offsetsStruct offsets = offsetsStruct(),
    const std::vector<std::string> uniformName = {},
    const drawInput drawData = drawInput()
    );

#endif  // ENGINE_ENGINE_DRAW_HPP_
