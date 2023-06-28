// "Copyright [2023] <Krzysztof Rudnicki>"
#ifndef DRAW_CPP
#define DRAW_CPP
#include "./draw.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <utility>
#include <vector>
#include <cstring>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "./constants.hpp"
#include "./misc.hpp"
#include "./renderLoop.hpp"
#include "./shader.hpp"
#include "./shaders.hpp"
#include "./stb_image.h"
#include "./textures.hpp"

drawFigureReturn drawFigure(const drawInput drawData) {
  switch (drawData.whatToDraw) {
    case 0:
      return draw(constants::VERTEX_SHADER_SOURCE_FILENAME,
                  constants::FRAGMENT_SHADER_SOURCE_FILENAME,
                  constants::TRIANGLE_VERTICES,
                  constants::TRIANGLE_VERTICES_SIZE);
    case 1:
      return draw(
        constants::VERTEX_SHADER_SOURCE_FILENAME,
        constants::FRAGMENT_SHADER_SOURCE_FILENAME,
        constants::SQUARE_VERTICES, constants::SQUARE_VERTICES_SIZE,
        constants::SQUARE_INDICES, constants::SQUARE_INDICES_SIZE);
    case 2:
      // Try to draw 2 triangles next to each other
      // using glDrawArrays by adding more vertices to your data.
      return draw(constants::VERTEX_SHADER_SOURCE_FILENAME,
                               constants::FRAGMENT_SHADER_SOURCE_FILENAME,
                               constants::TRIANGLES_VERTICES,
                               constants::TRIANGLES_VERTICES_SIZE,
                               constants::TRIANGLES_INDICES,
                               constants::TRIANGLES_INDICES_SIZE);
    case 3:
      draw(constants::VERTEX_SHADER_SOURCE_FILENAME,
                        constants::FRAGMENT_SHADER_SOURCE_FILENAME,
                        constants::TRIANGLE_ONE, constants::TRIANGLE_ONE_SIZE);
      // Now create the same 2 triangles
      // using two different VAOs and VBOs for their data
      return draw(constants::VERTEX_SHADER_SOURCE_FILENAME,
                               constants::FRAGMENT_SHADER_SOURCE_FILENAME,
                               constants::TRIANGLE_TWO,
                               constants::TRIANGLE_TWO_SIZE);
    case 4:
      draw(constants::VERTEX_SHADER_SOURCE_FILENAME,
                        constants::FRAGMENT_SHADER_SOURCE_FILENAME,
                        constants::TRIANGLE_ONE, constants::TRIANGLE_ONE_SIZE);
      /*
      Create two shader programs where
      the second program uses a different
      fragment shader that outputs the color yellow;
      draw both triangles again where one outputs the color yellow
      */
      return draw(
          constants::VERTEX_SHADER_SOURCE_FILENAME,
          constants::FRAGMENT_SHADER_SOURCE_YELLOW_FILENAME,
          constants::TRIANGLE_TWO, constants::TRIANGLE_TWO_SIZE);
    case 5:
      // Get color from vertex shader to fragment shader
      return draw(
          constants::VERTEX_SHADER_COLOR_FILENAME,
          constants::FRAGMENT_SHADER_COLOR_FROM_VERTEX_FILENAME,
          constants::TRIANGLE_VERTICES, constants::TRIANGLE_VERTICES_SIZE);
    case 6:
    {
      offsetsStruct offsets = offsetsStruct();
      const std::vector<std::string> uniformInfo = {"ourColor"};
      // set color from opengl code to uniform value in fragment shader
      return draw(constants::VERTEX_SHADER_COLOR_FILENAME,
                              constants::FRAGMENT_SHADER_UNIFORMS_FILENAME,
                              constants::TRIANGLE_VERTICES,
                              constants::TRIANGLE_VERTICES_SIZE,
                              constants::TRIANGLE_INDICES,
                              constants::TRIANGLE_INDICES_SIZE,
                              false, false, {}, offsets, uniformInfo);
    }
    case 7:
      // set color from opengl code to uniform value in fragment shader
      return draw(
          constants::VERTEX_SHADER_VERTICE_COLOR_FILENAME,
          constants::FRAGMENT_SHADER_COLOR_FROM_VERTEX_FILENAME,
          constants::TRIANGLE_COLORS, constants::TRIANGLE_COLORS_SIZE,
          constants::TRIANGLE_INDICES,
          constants::TRIANGLE_INDICES_SIZE, true);
    case 8:
      // upside down triangle
      return draw(constants::VERTEX_SHADER_UPSIDE_DOWN_FILENAME,
                               constants::FRAGMENT_SHADER_SOURCE_FILENAME,
                               constants::TRIANGLE_VERTICES,
                               constants::TRIANGLE_VERTICES_SIZE);
    case 9: {
      // offset triangle
      offsetsStruct offsets = offsetsStruct();
      offsets.xOffset = 0.5f;
      return draw(constants::VERTEX_SHADER_OFFSET_FILENAME,
                               constants::FRAGMENT_SHADER_SOURCE_FILENAME,
                               constants::TRIANGLE_VERTICES,
                               constants::TRIANGLE_VERTICES_SIZE,
                               constants::TRIANGLE_INDICES,
                               constants::TRIANGLE_INDICES_SIZE,
                               false, false, {}, offsets);
    }
    case 10:
      return draw(constants::VERTEX_SHADER_TASK_THREE_FILENAME,
                               constants::FRAGMENT_SHADER_TASK_THREE_FILENAME,
                               constants::TRIANGLE_VERTICES,
                               constants::TRIANGLE_VERTICES_SIZE);
    case 11: {
        std::vector<textureArgument> textureInfoArray = {
          texture_constants::CONTAINER_ARGUMENT,
          texture_constants::AWESOME_FACE_ARGUMENT
        };
      return draw(
          constants::VERTEX_SHADER_TEXTURE_FILENAME,
          constants::FRAGMENT_SHADER_TEXTURE_FILENAME,
          constants::TEXTURE_VERTICES, constants::TEXTURE_VERTICES_SIZE,
          constants::TEXTURE_INDICES,
          constants::TEXTURE_INDICES_SIZE,
          true, true, textureInfoArray);
    }
    case 12: {
        std::vector<textureArgument> textureInfoArray = {
          texture_constants::CONTAINER_ARGUMENT,
          texture_constants::AWESOME_FACE_ARGUMENT
        };
        return draw(
        constants::VERTEX_SHADER_TEXTURE_FILENAME,
        constants::FRAGMENT_SHADER_TEXTURE_TASK_ONE_FILENAME,
        constants::TEXTURE_VERTICES, constants::TEXTURE_VERTICES_SIZE,
        constants::TEXTURE_INDICES,
        constants::TEXTURE_INDICES_SIZE,
        true, true, textureInfoArray);
    }
    case 13: {
        std::vector<textureArgument> textureInfoArray = {
          texture_constants::CONTAINER_ARGUMENT,
          texture_constants::AWESOME_FACE_ARGUMENT
        };
        return draw(
        constants::VERTEX_SHADER_TEXTURE_FILENAME,
        constants::FRAGMENT_SHADER_TEXTURE_FILENAME,
        constants::TEXTURE_VERTICES_2F, constants::TEXTURE_VERTICES_2F_SIZE,
        constants::TEXTURE_INDICES,
        constants::TEXTURE_INDICES_SIZE,
        true, true, textureInfoArray);
    }
    case 14: {
        std::vector<textureArgument> textureInfoArray = {
          texture_constants::TEXTURE_TASK_THREE_CONTAINER_ARGUMENT,
          texture_constants::TEXTURE_TASK_THREE_FACE_ARGUMENT
        };
        return draw(
        constants::VERTEX_SHADER_TEXTURE_FILENAME,
        constants::FRAGMENT_SHADER_TEXTURE_FILENAME,
        constants::TEXTURE_VERTICES_TASK_THREE,
        constants::TEXTURE_VERTICES_TASK_THREE_SIZE,
        constants::TEXTURE_INDICES,
        constants::TEXTURE_INDICES_SIZE,
        true, true, textureInfoArray);
    }
    case constants::MAX_DRAW_CALL: {
        std::vector<textureArgument> textureInfoArray = {
          texture_constants::CONTAINER_ARGUMENT,
          texture_constants::AWESOME_FACE_ARGUMENT
        };
        offsetsStruct offsets = offsetsStruct();
        const std::vector<std::string> uniformInfo = {"mixProportions"};
        return draw(
        constants::VERTEX_SHADER_TEXTURE_FILENAME,
        constants::FRAGMENT_SHADER_TEXTURE_UNIFORM_FILENAME,
        constants::TEXTURE_VERTICES,
        constants::TEXTURE_VERTICES_SIZE,
        constants::TEXTURE_INDICES,
        constants::TEXTURE_INDICES_SIZE,
        true, true, textureInfoArray,
        offsets, uniformInfo, drawData);
    }
    default:
      throw "No function for this draw call";
  }
}

unsigned int getShaderProgram(const char* vertexShaderSource,
                              const char* fragmentShaderSource) {
  const std::pair<unsigned int, unsigned int> shaders =
      compileShaders(vertexShaderSource, fragmentShaderSource);
  if (shaders.first == 0 || shaders.second == 0) return 0;

  const unsigned int shaderProgram =
      linkShaderObjectsShaderProgram(shaders.first, shaders.second);

  if (shaderProgram == 0) return 0;
  return shaderProgram;
}

void setOffsets(Shader shader, const offsetsStruct offsets) {
  shader.setFloat("xOffset", offsets.xOffset);
  shader.setFloat("yOffset", offsets.yOffset);
  shader.setFloat("zOffset", offsets.zOffset);
}

drawFigureReturn draw(const char* vertexPath, const char* fragmentPath,
                      const float vertices[],
                      const size_t verticesSize,
                      const unsigned int indices[],
                      const size_t indicesSize,
                      const bool colorIncluded,
                      const bool textureIncluded,
                      std::vector<textureArgument> textureInfo,
                      const offsetsStruct offsets,
                      const std::vector<std::string> uniformName,
                      const drawInput drawData) {
  // https://stackoverflow.com/questions/33883609/opengl-linker-error-linking-with-uncompiled-shader
  Shader ourShader(vertexPath,
                   fragmentPath);
  ourShader.use();
  setOffsets(ourShader, offsets);

  unsigned int VBO =
    copyVerticesMemory(vertices, verticesSize, GL_ARRAY_BUFFER);
  unsigned int VAO = generateBindVAO();
  copyVerticesArray(VBO, vertices, verticesSize,
                  GL_ARRAY_BUFFER);
  unsigned int EBO =
      copyVerticesMemory(indices, indicesSize, GL_ELEMENT_ARRAY_BUFFER);

  configureVertexAttribute(colorIncluded, textureIncluded);
  if (uniformName.size() > 0) {
    if(uniformName.at(0) == "ourColor") {
      updateUniformColor(ourShader, uniformName.at(0));
    }
    if(uniformName.at(0) == "mixProportions") {
      srand (time(NULL));
      // const float randomNumber = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      std::cout << drawData.whatToDraw << std::endl;
      ourShader.setFloat(uniformName.at(0), drawData.textureOpacity);
    }
  }

  drawTextureArray(textureInfo, ourShader);
  // unsigned int texture1 = loadAndCreateTexture(
  // textureInfo.texturePath,
  // textureInfo.flipImage,
  // textureInfo.wrappingMethod);
  // unsigned int texture2 = loadAndCreateTexture(
  // "assets/awesomeface.png", false, GL_REPEAT);

  // ourShader.setInt("texture1", 0);
  // ourShader.setInt("texture2", 1);

  // don't forget to activate/use
  // the shader before setting uniforms!
  // set it via the texture class
  // (texture1, GL_TEXTURE0);
  // activateAndBindTextures(texture2, GL_TEXTURE1);

  glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  drawFigureReturn newReturn;
  newReturn.success = 0;
  newReturn.VAO = VAO;
  newReturn.VBO = VBO;
  newReturn.EBO = EBO;
  return newReturn;
}

void updateUniformColor(const Shader shaderProgram,
                        std::string uniformName) {
  // update the uniform color
  const float timeValue = glfwGetTime();  // retrieve running time
  const float greenValue = sin(timeValue) / 2.0f + 0.5f;
  // vary the color from 0.0 to 1.0 using sin
  // query the location of our uniform
  shaderProgram.set4Float(uniformName, 0.0f, greenValue, 0.0f, 1.0f);
  // if glGetUniformLocation returns -1 it could not find the location
    /* we set the uniform value using glUniform4f
    4f means that it expects 4 floats
    few of possible postfixes:
        f: the function expects a float as its value.
        i: the function expects an int as its value.
        ui: the function expects an unsigned int as its value.
        3f: the function expects 3 floats as its value.
        fv: the function expects a float vector/array as its value.
    */
  }

#endif  // #ifndef DRAW_CPP
