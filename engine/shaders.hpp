// "Copyright [2023] <Krzysztof Rudnicki>"
#ifndef ENGINE_ENGINE_SHADERS_HPP_
#define ENGINE_ENGINE_SHADERS_HPP_
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <utility>

unsigned int linkShaderObjectsShaderProgram(const unsigned int vertexShaders,
                                            const unsigned int fragmentShader);

std::pair<unsigned int, unsigned int> compileShaders(
    const char* vertexShaderSource, const char* fragmentShaderSource);

unsigned int compileShader(const GLenum shaderType, const char* shaderSource);
int shaderCompilationSuccessful(const unsigned int shader);
int shaderProgramLinkingSuccessful(const unsigned int shaderProgram);
int shaderSuccessful(const unsigned int shader, const bool compilation);
void shaderFailedMessage(const unsigned int shader, const bool compilation);

#endif  // ENGINE_ENGINE_SHADERS_HPP_
