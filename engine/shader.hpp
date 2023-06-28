// "Copyright [2023] <Krzysztof Rudnicki>"
#ifndef ENGINE_ENGINE_SHADER_HPP_
#define ENGINE_ENGINE_SHADER_HPP_

#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
 public:
  unsigned int ID;
  // constructor generates the shader on the fly
  // ------------------------------------------------------------------------
  Shader(const std::string vertexPath, const std::string fragmentPath);
  const std::string fileToShader(const std::string shaderPath);
  // activate the shader
  // ------------------------------------------------------------------------
  void use();
  // utility uniform functions
  // ------------------------------------------------------------------------
  void setBool(const std::string &name, bool value) const;
  // ------------------------------------------------------------------------
  void setInt(const std::string &name, int value) const;
  // ------------------------------------------------------------------------
  void setFloat(const std::string &name, float value) const;

  void set4Float(const std::string &name, const float floatOne, const float floatTwo, const float floatThree, const float floatFour) const;

 private:
  // utility function for checking shader compilation/linking errors.
  // ------------------------------------------------------------------------
  void checkCompileErrors(unsigned int shader, std::string type);

  void compileErrorsMessage(const unsigned int shader, const bool compilation,
                            const std::string type,
                            const std::string errorMessage);
};
#endif  // ENGINE_ENGINE_SHADER_HPP_
