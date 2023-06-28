// "Copyright [2023] <Krzysztof Rudnicki>"
#ifndef MAIN_CPP
#define MAIN_CPP
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <random>
// I am using standard library RNG because
// I am lazy and wanted to create quick code snippet upgrade to this:
// https://arvid.io/2018/06/30/on-cxx-random-number-generator-quality/
// whenever, if ever I feel like it

#include "./beforeRender.hpp"
#include "./constants.hpp"
#include "./misc.hpp"
#include "./renderLoop.hpp"

int main() {
  // changed in glfwWindowShouldClose
  GLFWwindow *window = prepareForRender();
  if (window == nullptr) return -1;
  renderLoop(window);

  // clean GLFW resources
  glfwTerminate();
  return 0;
}

#endif  // #ifndef MAIN_CPP
