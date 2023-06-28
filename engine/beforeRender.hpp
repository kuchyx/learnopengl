// "Copyright [2023] <Krzysztof Rudnicki>"
#ifndef ENGINE_ENGINE_BEFORERENDER_HPP_
#define ENGINE_ENGINE_BEFORERENDER_HPP_
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void configureGLFW(const int GLFWMajorVersion, const int GLFWMinorVersion);
void instantiateGLFWwindow();
GLFWwindow *createWindowObject();
int initializeGLAD();
void framebuffer_size_callback(GLFWwindow *window, const int width,
                               const int height);
void viewPort(GLFWwindow *window);
GLFWwindow *prepareForRender();

#endif  // ENGINE_ENGINE_BEFORERENDER_HPP_
