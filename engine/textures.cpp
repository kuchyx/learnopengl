// "Copyright [2023] <Krzysztof Rudnicki>"
#ifndef TEXTURES_CPP
#define TEXTURES_CPP
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <vector>
#include <iostream>    
#include <array> 
#include "./textures.hpp"
#include "./stb_image.h"
#include "./shader.hpp"

void setTextureSCoordinate(const GLenum textureTarget,
                           const GLint sCoordinateOption,
                           const float* borderColor) {
  // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexParameter.xhtml
  // first argument is texture target (by default we work with 2D textures so it
  // will be GL_TEXTURE_2D) second argument is what option we want to set and
  // for which texture axis (s, t or r) Third argument is texture wrapping mode
  glTexParameteri(textureTarget, GL_TEXTURE_WRAP_S, sCoordinateOption);
  if (sCoordinateOption == GL_CLAMP_TO_BORDER && borderColor != NULL) {
    // if we use GL_CLAMP_TO_BORDER all of the space that is not occupied by
    // texture will be occupied by color we pass the color we want to use in
    // float array (RGB + transparency)
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
  }
}

void setTextureTCoordinate(const GLenum textureTarget,
                           const GLint tCoordinateOption,
                           const float* borderColor) {
  // for comments concerning glTexParameteri and glTexParameterfv go to
  // setTextureSCoordinate function
  if (textureTarget == GL_TEXTURE_2D || textureTarget == GL_TEXTURE_3D) {
    glTexParameteri(textureTarget, GL_TEXTURE_WRAP_T, tCoordinateOption);
    if (tCoordinateOption == GL_CLAMP_TO_BORDER && borderColor != NULL) {
      glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    }
  }
}

void setTextureRCoordinate(const GLenum textureTarget,
                           const GLint rCoordinateOption,
                           const float* borderColor) {
  // for comments concerning glTexParameteri and glTexParameterfv go to
  // setTextureSCoordinate function
  if (textureTarget == GL_TEXTURE_3D) {
    glTexParameteri(textureTarget, GL_TEXTURE_WRAP_R, rCoordinateOption);
    if (rCoordinateOption == GL_CLAMP_TO_BORDER && borderColor != NULL) {
      glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    }
  }
}

// Coordinate options can be: GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE,
// GL_CLAMP_TO_BORDER s t r are equivalent to x y z
void setTextureParametersINT(const GLenum textureTarget,
                             const GLint sCoordinateOption,
                             const GLint tCoordinateOption,
                             const GLint rCoordinateOption,
                             const float* borderColor) {
  setTextureSCoordinate(textureTarget, sCoordinateOption, borderColor);
  setTextureTCoordinate(textureTarget, tCoordinateOption, borderColor);
  setTextureRCoordinate(textureTarget, rCoordinateOption, borderColor);
}

void setTextureFilteringAndMipMap(const GLenum textureTarget,
                                  const GLenum filterType,
                                  const GLint textureFilteringMethod,
                                  const GLint mipMapFilteringMethod) {
  // mipMapFilteringMethod can be equal to: GL_NEAREST_MIPMAP_NEAREST,
  // GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR
  // NEAREST_MIPMAP - take nearest mipmap to match pixel size
  // LINEAR_MIPMAP - interpolate between two mipmaps that match the size of a
  // pixel NEAREST (at the end) - samples texture based on nearest neighbor
  // interpolation LINEAR (at the end) - samples texture using linear
  // interpolation setting anything else than GL_TEXTURE_MIN_FILTER as a second
  // parameter results in GL_INVALID_ENUM error
  glTexParameteri(textureTarget, GL_TEXTURE_MIN_FILTER, mipMapFilteringMethod);
  // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexParameter.xhtml
  // first argument is texture target (by default we work with 2D textures so it
  // will be GL_TEXTURE_2D) second argument is specifying whether this filter
  // works for magnifying textures GL_TEXTURE_MAG_FILTER or minifying
  // GL_TEXTURE_MIN_FILTER third argument is how we should magnify/minify
  // textures, whether we should choose the color of pixel closest to the
  // coordinates GL_NEAREST (default) or should we blend the neighboring pixels
  // and choose blended color GL_LINEAR
  glTexParameteri(textureTarget, filterType, textureFilteringMethod);
}

unsigned int generateAndBindTexture(const GLenum textureTarget,
                                    const GLsizei numberOfTextures) {
  unsigned int texture;
  // first argument is how many textures we want to generate
  // second is an array of unsigned int in which we will store id of those
  // textures
  glGenTextures(numberOfTextures, &texture);
  // then we bind texture
  glBindTexture(textureTarget, texture);
  return texture;
}

unsigned int loadAndBindTextureFile(unsigned int texture,
                                    const char* texturePath, bool flipImage) {
  int textureWidth, textureHeight, colorChannels;
  stbi_set_flip_vertically_on_load(flipImage);
  unsigned char* data = stbi_load(texturePath, &textureWidth, &textureHeight,
                                  &colorChannels, STBI_rgb_alpha);
  if (data) {
    // generate texture
    /*
        first argument is texture target, setting it to GL_TEXTURE_2D will only
       affect 2D targets and not 1D or 3D 2nd is mipmap level for which to
       create texture, base level is 0 3rd is in what format we want to store
       texture (our image has only rgb values so rgb) 4th and 5th are the width
       and height of texture 6th argument is always 0 (legacy, its called border
       parameter) 7th and 8th are the format and datatype of source image, we
       store the image data as chars (bytes) so we pass that 9th last argument
       is actual data of the texture
    */
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    // after generating texture, lets free the memory from image
    stbi_image_free(data);
    return texture;
  } else {
    std::cout << "Failed to load texture! " << std::endl;
    return -1;
  }
}

void drawTextureArray(const std::vector<textureArgument> texturesInfo, Shader ourShader) {
  std::vector<unsigned int> texture;
  uint64_t arrayLength = texturesInfo.size();
  for (uint64_t i = 0; i <  arrayLength; i++) {
    const unsigned int tempTexture = loadAndCreateTexture(
    texturesInfo.at(i).texturePath,
    texturesInfo.at(i).flipImage,
    texturesInfo.at(i).wrappingMethod);
    texture.push_back(tempTexture);

    // don't forget to activate/use
    // the shader before setting uniforms!
    // set it via the texture class
  }
  for (uint64_t i = 1; i <= texture.size(); i++) {
    const std::string textureString = "texture" + std::to_string(i);
    ourShader.setInt(textureString, i - 1);
  }

  for (uint64_t i = 0; i <  texture.size(); i++) {
    activateAndBindTextures(texture.at(i), GL_TEXTURE0 + i);
  }
}

// const char* texturePath, int textureWidth, int textureHeight, int
// colorChannels, const GLenum textureTarget, const GLint sCoordinateOption,
// const GLint tCoordinateOption, const GLint rCoordinateOption, const float*
// borderColor
unsigned int loadAndCreateTexture(
  const char* texturePath, bool flipImage, GLint wrappingMethod) {
  // load and create a texture
  // -------------------------
  unsigned int texture = generateAndBindTexture(GL_TEXTURE_2D, 1);
  setTextureParametersINT(GL_TEXTURE_2D, wrappingMethod, wrappingMethod);

  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  texture = loadAndBindTextureFile(texture, texturePath, flipImage);
  return texture;
}

void activateAndBindTextures(unsigned int texture, GLenum textureNumber) {
  glActiveTexture(textureNumber);
  glBindTexture(GL_TEXTURE_2D, texture);
}

#endif  // TEXTURES_CPP
