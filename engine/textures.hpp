// "Copyright [2023] <Krzysztof Rudnicki>"
#ifndef ENGINE_ENGINE_TEXTURES_HPP_
#define ENGINE_ENGINE_TEXTURES_HPP_
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "./constants.hpp"
#include "./shader.hpp"
#include <iostream>
#include <vector>

  struct textureArgument {
    textureArgument() :
      texturePath(constants::NO_TEXTURE_TEXTURE),
      flipImage(false), wrappingMethod(GL_REPEAT) {}
    textureArgument(const char* tP, const bool fI, const GLint wM) :
      texturePath(tP),
      flipImage(fI),
      wrappingMethod(wM) {}
    const char* texturePath;
    bool flipImage;
    GLint wrappingMethod;
  };

namespace texture_constants {
  inline const textureArgument CONTAINER_ARGUMENT = 
    textureArgument(constants::CONTAINER_TEXTURE, true, GL_CLAMP_TO_EDGE);
  inline const textureArgument AWESOME_FACE_ARGUMENT = 
    textureArgument(constants::AWESOME_FACE_TEXTURE, false, GL_REPEAT);
  inline const textureArgument TEXTURE_TASK_THREE_CONTAINER_ARGUMENT =
    textureArgument(constants::CONTAINER_TEXTURE, true, GL_NEAREST);
  inline const textureArgument TEXTURE_TASK_THREE_FACE_ARGUMENT =
    textureArgument(constants::AWESOME_FACE_TEXTURE, false, GL_NEAREST);

}

void setTextureParametersINT(const GLenum textureTarget = GL_TEXTURE_2D,
                             const GLint sCoordinateOption = GL_REPEAT,
                             const GLint tCoordinateOption = GL_REPEAT,
                             const GLint rCoordinateOption = GL_REPEAT,
                             const float* borderColor = NULL);
void setTextureSCoordinate(const GLenum textureTarget = GL_TEXTURE_2D,
                           const GLint sCoordinateOption = GL_REPEAT,
                           const float* borderColor = NULL);
void setTextureTCoordinate(const GLenum textureTarget = GL_TEXTURE_2D,
                           const GLint tCoordinateOption = GL_REPEAT,
                           const float* borderColor = NULL);
void setTextureRCoordinate(const GLenum textureTarget = GL_TEXTURE_3D,
                           const GLint rCoordinateOption = GL_REPEAT,
                           const float* borderColor = NULL);
void setTextureFilteringAndMipMap(
    const GLenum textureTarget = GL_TEXTURE_2D,
    const GLenum filterType = GL_TEXTURE_MAG_FILTER,
    const GLint textureFilteringMethod = GL_NEAREST,
    const GLint mipMapFilteringMethod = GL_NEAREST_MIPMAP_NEAREST);
unsigned int generateAndBindTexture(const GLenum textureTarget);

// const char* texturePath, int textureWidth, int textureHeight, int
// colorChannels, const GLenum textureTarget, const GLint sCoordinateOption,
// const GLint tCoordinateOption, const GLint rCoordinateOption, const float*
// borderColor
unsigned int loadAndCreateTexture(const char* texturePath, bool flipImage, GLint wrappingMethod);
void activateAndBindTextures(unsigned int texture, GLenum textureNumber);
unsigned int loadAndBindTextureFile(unsigned int texture,
                                    const char* texturePath, bool flipImage);
void drawTextureArray(const std::vector<textureArgument> texturesInfo, Shader ourShader);

#endif  // ENGINE_ENGINE_TEXTURES_HPP_