// "Copyright [2023] <Krzysztof Rudnicki>"
#ifndef ENGINE_ENGINE_RENDERLOOP_HPP_
#define ENGINE_ENGINE_RENDERLOOP_HPP_
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

struct drawInput {
    drawInput() : whatToDraw(0), textureOpacity(0) {}
    int whatToDraw;
    float textureOpacity;
};

void renderLoop(GLFWwindow *window);
drawInput renderLoopInside(GLFWwindow *window, drawInput drawData);

void copyVerticesArray(unsigned int vertexBufferObject, const float vertices[],
                       const size_t sizeOfVertices,
                       const GLenum boundBufferTarget);

unsigned int generateBindVAO();

void configureVertexAttribute(const bool colorIncluded,
                              const bool textureIncluded);

drawInput processInput(GLFWwindow *window, drawInput drawData);

unsigned int copyVerticesMemory(const float vertices[],
                                const size_t sizeOfVertices,
                                const GLenum boundBufferTarget);

unsigned int copyVerticesMemory(const unsigned int vertices[],
                                const size_t sizeOfVertices,
                                const GLenum boundBufferTarget);

#endif  // ENGINE_ENGINE_RENDERLOOP_HPP_
