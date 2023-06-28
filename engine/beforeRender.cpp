// "Copyright [2023] <Krzysztof Rudnicki>"
#ifndef BEFORE_RENDER_CPP
#define BEFORE_RENDER_CPP
#include "./beforeRender.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "./constants.hpp"
#include "./misc.hpp"

void configureGLFW(const int GLFWMajorVersion, const int GLFWMinorVersion) {
  // first argument tells us what option to configure
  // second is to what we set the value of this option
  // see: https://www.glfw.org/docs/latest/window.html#window_hints
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFWMajorVersion);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFWMinorVersion);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// we set GLFW to 3.3 CORE
// core profile gives us access to smaller subset of
// OGL without backwards compatible features

// if we are on Mac OS X we need this for our code to work
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void instantiateGLFWwindow() {
  // Initialize GLFW
  glfwInit();
  configureGLFW(constants::GLFW_MAJOR_VERSION, constants::GLFW_MINOR_VERSION);
}

GLFWwindow *createWindowObject() {
  // First two arguments are width and height
  // Third is the name of the window
  // We ignore last two
  GLFWwindow *window = glfwCreateWindow(
      constants::MAIN_WINDOW_WIDTH, constants::MAIN_WINDOW_HEIGHT,
      constants::MAIN_WINDOW_NAME, nullptr, nullptr);
  return window;
}

int initializeGLAD() {
  // we load address of OGL OS-specific function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    print("Failed to initialize GLAD");
    return -1;
  }
  return 0;
}

// resizes viewport when user resizes window
void framebuffer_size_callback(GLFWwindow *window, const int width,
                               const int height) {
  glViewport(0, 0, width, height);
}

void viewPort(GLFWwindow *window) {
  // We tell OGL size of rendering window
  // First two define left corner of window
  // 3th and 4th width and height of rendering window
  // we could set them to be smaller than window dimension,
  // ogl rendering will be then displayed in smaller window
  glViewport(0, 0, constants::MAIN_WINDOW_WIDTH, constants::MAIN_WINDOW_HEIGHT);
  // processed coordinates are between -1 and 1 so here we map:
  // (-1 to 1) to (0, constants::MAIN_WINDOW_WIDTH)
  // and (0, constants::MAIN_WINDOW_HEIGHT)
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  // we call framebuffer_size_callback on every window resize
}

GLFWwindow *prepareForRender() {
  instantiateGLFWwindow();

  GLFWwindow *window = createWindowObject();
  // function returns GLFWWindow object

  if (window == nullptr) {
    print("Failed to create GLFW window");
    glfwTerminate();
    return window;
  }
  // we make context of this window main context of current thread
  glfwMakeContextCurrent(window);

  if (initializeGLAD() == -1) return nullptr;
  viewPort(window);
  return window;
}

#endif
