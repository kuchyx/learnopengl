// "Copyright [2023] <Krzysztof Rudnicki>"
#ifndef SHADERS_CPP
#define SHADERS_CPP
#include "./shaders.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./constants.hpp"
#include "./misc.hpp"

unsigned int linkShaderObjectsShaderProgram(const unsigned int vertexShaders,
                                            const unsigned int fragmentShader) {
  // link shader objects into shader program
  // will store shader program id
  // creates program
  const unsigned int shaderProgram = glCreateProgram();

  // attachShaders
  glAttachShader(shaderProgram, vertexShaders);
  glAttachShader(shaderProgram, fragmentShader);

  // link shaders
  glLinkProgram(shaderProgram);
  if (!shaderSuccessful(shaderProgram, false)) return 0;

  // activate program
  // after that every shader and rendering call will use this program object
  glUseProgram(shaderProgram);

  // delete shaders
  // (they are linked into shaderProgram and we do not need them anymore)
  glDeleteShader(vertexShaders);
  glDeleteShader(fragmentShader);
  if (shaderProgram == 0) print("Shader Program Linking Failed");
  return shaderProgram;
}

unsigned int compileShader(const GLenum shaderType, const char* shaderSource) {
  // we create vertex shader and assign its id to shader variable
  const unsigned int shaderID = glCreateShader(shaderType);

  // attach shader source code to shader object
  // from left: shader object to compile,
  // how many strings as source code, actual source code
  // (we leave the 4th as nullptr)
  glShaderSource(shaderID, 1, &shaderSource, nullptr);
  // compile shader
  glCompileShader(shaderID);
  if (!shaderSuccessful(shaderID, true)) return 0;
  return shaderID;
}

std::pair<unsigned int, unsigned int> compileShaders(
    const char* vertexShaderSource, const char* fragmentShaderSource) {
  const unsigned int vertexShader =
      compileShader(GL_VERTEX_SHADER, vertexShaderSource);

  if (vertexShader == 0) {
    print("Vertex Shader Compilation Failed");
    return std::make_pair(0, 0);
  }

  const unsigned int fragmentShader =
      compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

  if (fragmentShader == 0) {
    print("Fragment Shader Compilation Failed");
    return std::make_pair(0, 0);
  }
  return std::make_pair(vertexShader, fragmentShader);
}

void shaderFailedMessage(const unsigned int shader, const bool compilation) {
  char infoLog[512];
  const size_t sizeOfInfoLog = sizeof(infoLog) / sizeof(infoLog[0]);
  compilation ? glGetShaderInfoLog(shader, sizeOfInfoLog, nullptr, infoLog)
              : glGetProgramInfoLog(shader, sizeOfInfoLog, nullptr, infoLog);
  std::cout << "ERROR vertex shader compilation failed \n"
            << infoLog << std::endl;
}

int shaderSuccessful(const unsigned int shader, const bool compilation) {
  // check if compilation was successful
  // int because glGetShaderiv requires int
  int success;
  // here we store info about compilation
  // check if compilation was successful
  compilation ? glGetShaderiv(shader, GL_COMPILE_STATUS, &success)
              : glGetProgramiv(shader, GL_LINK_STATUS, &success);
  // if not display compilation log
  if (!success) {
    shaderFailedMessage(shader, compilation);
  }
  return success;
}

#endif
