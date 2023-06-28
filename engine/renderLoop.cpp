// "Copyright [2023] <Krzysztof Rudnicki>"
#ifndef RENDER_LOOP_CPP
#define RENDER_LOOP_CPP
#include "./renderLoop.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "./constants.hpp"
#include "./draw.hpp"
#include "./misc.hpp"
#include "./shaders.hpp"

drawInput processInput(GLFWwindow *window, drawInput drawData) {
  static bool lockedLeft = false; // czemu są static ?
  static bool lockedRight = false;
  static bool lockedUp = false; 
  static bool lockedDown = false;
  const bool PRESSED_CHANGE_LEFT =
      (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS);
  const bool PRESSED_CHANGE_RIGHT =
      (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS);

  const bool PRESSED_CHANGE_UP =
      (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS);
  const bool PRESSED_CHANGE_DOWN =
      (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS);

  // glfwGetKey takes window and key as
  // an input and checks is currently being pressed
  // if the user pressed escape we close window
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
    
  if (!PRESSED_CHANGE_LEFT) lockedLeft = 0;
  if (!PRESSED_CHANGE_RIGHT) lockedRight = 0;
  if (!PRESSED_CHANGE_UP) lockedUp = 0;
  if (!PRESSED_CHANGE_DOWN) lockedDown = 0;


  if (PRESSED_CHANGE_RIGHT && lockedRight == 0) {
    lockedRight = 1;
    drawData.whatToDraw = (drawData.whatToDraw == constants::MAX_DRAW_CALL ? 0 : drawData.whatToDraw + 1);
    return drawData;
  }
  if (PRESSED_CHANGE_LEFT && lockedLeft == 0) {
    lockedLeft = 1;
    drawData.whatToDraw = (drawData.whatToDraw == 0 ? constants::MAX_DRAW_CALL : drawData.whatToDraw - 1);
    return drawData;
  }
  if (PRESSED_CHANGE_UP && lockedUp == 0) {
    lockedUp = 1;
    drawData.textureOpacity = drawData.textureOpacity + 0.1;
    std::cout << drawData.textureOpacity << std::endl;
    return drawData;
  }
  if (PRESSED_CHANGE_DOWN && lockedDown == 0) {
    lockedDown = 1;
    drawData.textureOpacity = drawData.textureOpacity - 0.1;
    return drawData;
  }
  return drawData;
}

// https://stackoverflow.com/a/25680092
unsigned int copyVerticesMemory(const float vertices[],
                                const size_t sizeOfVertices,
                                const GLenum boundBufferTarget) {
  // stores vertices in gpu memory
  unsigned int vertexBufferObject;
  // this is open gl object so we refer
  // it by its ID generated here and stored in vertexBufferObject variable
  glGenBuffers(1, &vertexBufferObject);
  // buffer type of vertex buffer object is GL_ARRAY_BUFFER
  glBindBuffer(boundBufferTarget, vertexBufferObject);
  // now whenever we change GL_ARRAY_BUFFER
  // we change bound buffer vertexBufferObject

  /* we copy vertex data into buffer memory
  GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few
  times. GL_STATIC_DRAW: the data is set only once and used many times.
  GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
  */
  glBufferData(boundBufferTarget, sizeOfVertices, vertices, GL_STATIC_DRAW);
  return vertexBufferObject;
}

unsigned int copyVerticesMemory(const unsigned int vertices[],
                                const size_t sizeOfVertices,
                                const GLenum boundBufferTarget) {
  // stores vertices in gpu memory
  unsigned int vertexBufferObject;
  // this is open gl object so we refer it
  // by its ID generated here and stored in vertexBufferObject variable
  glGenBuffers(1, &vertexBufferObject);
  // buffer type of vertex buffer object is GL_ARRAY_BUFFER
  glBindBuffer(boundBufferTarget, vertexBufferObject);
  // now whenever we change GL_ARRAY_BUFFER
  // we change bound buffer vertexBufferObject

  /* we copy vertex data into buffer memory
  GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few
  times. GL_STATIC_DRAW: the data is set only once and used many times.
  GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
  */
  glBufferData(boundBufferTarget, sizeOfVertices, vertices, GL_STATIC_DRAW);
  return vertexBufferObject;
}

void configureVertexAttribute(const bool colorIncluded,
                              const bool textureIncluded) {
  /* specify how OGL interprets vertex data
  From left:
  which vertex attribute we configure (from shader source code layout (location
  = 0)) size of vertex attribute (we use vec3 so it contains 3 values) type of
  data of which vec consists of should data be normalized, (useful when we use
  integer data) space between vertex attributes, each position data is 3 times
  the size of float offset of where position data begins in buffer see:
  https://learnopengl.com/img/getting-started/vertex_attribute_pointer.png
  vertex attribute data take data from memory managed by VBO bound to
  GL_ARRAY_BUFFER */
  if (!colorIncluded) {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          reinterpret_cast<void *>(0));
    // enable vertex attribute
    glEnableVertexAttribArray(0);
    return;
  }

  /* we change attribute location, color values have size of 3 floats
  we do not normalize values, in order to get the next attribute value in data
  array we need to move 6 floats, (3 for position and 3 for color), we also need
  to specify an offset, first we have position then after 3 floats we have color
  https://learnopengl.com/img/getting-started/vertex_attribute_pointer_interleaved.png
*/
  if (colorIncluded && !textureIncluded) {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          reinterpret_cast<void *>(0));
    // enable vertex attribute
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          reinterpret_cast<void *>(3 * sizeof(float)));
    // enable vertex attribute
    glEnableVertexAttribArray(1);
    return;
  }

  // Since we've added an extra vertex
  // attribute we again have to notify OpenGL of the new vertex format
  // this time for textures we add just
  // 2 more attributes and not 3 as with color
  if (textureIncluded) {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          reinterpret_cast<void *>(0));
    // enable vertex attribute
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          reinterpret_cast<void *>(3 * sizeof(float)));
    // enable vertex attribute
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          reinterpret_cast<void *>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    return;
  }
}

unsigned int generateBindVAO() {
  // vertex array object is used to draw objects by binding them to vao
  // generate vao
  unsigned int vertexArrayObject;
  glGenVertexArrays(1, &vertexArrayObject);
  // bind vao
  glBindVertexArray(vertexArrayObject);
  return vertexArrayObject;
}

void copyVerticesArray(const unsigned int vertexBufferObject,
                       const float vertices[], const size_t sizeOfVertices,
                       const GLenum boundBufferTarget) {
  // copy vertices array in array useful for OGL
  glBindBuffer(boundBufferTarget, vertexBufferObject);
  glBufferData(boundBufferTarget, sizeOfVertices, vertices, GL_STATIC_DRAW);
}

drawInput renderLoopInside(GLFWwindow *window, drawInput drawData) {
  // input
  drawData = processInput(window, drawData);
  // We specify the color to clear the screen with
  // RGB and alpha value
  glClearColor(constants::LEARN_OPEN_GL_COLOR.red,
               constants::LEARN_OPEN_GL_COLOR.green,
               constants::LEARN_OPEN_GL_COLOR.blue,
               constants::LEARN_OPEN_GL_COLOR.alpha);
  // There is
  // GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT and GL_STENCIL_BUFFER_BIT
  glClear(GL_COLOR_BUFFER_BIT);

  drawFigureReturn successAndVao = drawFigure(drawData);
  if (successAndVao.success == -1) {
    print("error with drawing!");
    glfwSetWindowShouldClose(window, true);
  }

  // swaps buffer containing color values of each pixel in window
  // there is front buffer (final image)
  // and back buffer (where all rendering commands draw to)
  // when back buffer is ready we swap it
  // with front buffer to eliminate flickering
  glfwSwapBuffers(window);

  // glfwPollEvents checks if any event
  // (like mouse/keyboard input was triggered),
  // updates window state and calls functions
  // (which we register via callback methods)
  glfwPollEvents();

  return drawData;
}

void renderLoop(GLFWwindow *window) {
  drawInput drawData = drawInput();
  // glfwWindowShouldClose checks if GLFW was instructed to close
  while (!glfwWindowShouldClose(window)) {
    drawData = renderLoopInside(window, drawData);
  }
}

#endif
