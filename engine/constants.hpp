// "Copyright [2023] <Krzysztof Rudnicki>"
#ifndef ENGINE_ENGINE_CONSTANTS_HPP_
#define ENGINE_ENGINE_CONSTANTS_HPP_
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string_view>

namespace constants {
    inline constexpr int GLFW_MAJOR_VERSION{3};
    inline constexpr int GLFW_MINOR_VERSION{3};
    // best practice is to use inline constexpr
    // std::string_view but glfwCreateWindow takes only char* as input
    inline const char* MAIN_WINDOW_NAME{"Match"};
    inline constexpr int MAIN_WINDOW_WIDTH{800};
    inline constexpr int MAIN_WINDOW_HEIGHT{600};
    inline constexpr struct {
    GLfloat red = 1.0f;
    GLfloat green = 0.0f;
    GLfloat blue = 0.0f;
    GLfloat alpha = 1.0f;
    } RED;

    inline constexpr struct {
    GLfloat red = 1.0f;
    GLfloat green = 1.0f;
    GLfloat blue = 1.0f;
    GLfloat alpha = 1.0f;
    } WHITE;

    inline constexpr struct {
    GLfloat red = 0.2f;
    GLfloat green = 0.3f;
    GLfloat blue = 0.3f;
    GLfloat alpha = 1.0f;
    } LEARN_OPEN_GL_COLOR;

    inline const char* NO_TEXTURE_TEXTURE = {
        "assets/Textures/no_texture.png"
    };

    inline const char* AWESOME_FACE_TEXTURE = {
        "assets/awesomeface.png"
    };

    inline const char* CONTAINER_TEXTURE = {
        "assets/container.png"
    };



    inline const char* VERTEX_SHADER_COLOR_FILENAME{
        "./Shaders/vertexShaderColor.vs"};

    inline const char* VERTEX_SHADER_UPSIDE_DOWN_FILENAME{
        "./Shaders/vertexShaderUpsideDown.vs"};

    inline const char* VERTEX_SHADER_OFFSET_FILENAME{
        "./Shaders/vertexShaderOffset.vs"};
    // we write vertex shader
    // version of glsl (since ogl 3.3 same as ogl so we pick 330)
    // in this shader we just forward input data to shader output
    // DO NOT REMOVE UNTIL CAN DRAW SQUARE USING CLASS
    inline const char* VERTEX_SHADER_SOURCE{
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0"};
    inline const char* VERTEX_SHADER_SOURCE_FILENAME{
        "./Shaders/vertexShaderSource.vs"};

    inline const char* VERTEX_SHADER_VERTICE_COLOR_FILENAME{
        "./Shaders/vertexShaderVerticeColor.vs"};

    inline const char* VERTEX_SHADER_TASK_THREE_FILENAME{
        "./Shaders/vertexShaderTaskThree.vs"};

    inline const char* VERTEX_SHADER_TEXTURE_FILENAME{
        "./Shaders/vertexShaderTexture.vs"};

    inline const char* FRAGMENT_SHADER_TASK_THREE_FILENAME{
        "./Shaders/fragmentShaderTaskThree.fs"};

    inline const char* FRAGMENT_SHADER_COLOR_FROM_VERTEX_FILENAME{
        "./Shaders/fragmentShaderColorFromVertex.fs"};

    inline const char* FRAGMENT_SHADER_UNIFORMS_FILENAME{
        "./Shaders/fragmentShaderUniforms.fs"};

    // write fragment shader
    // we set the color of each pixel to be orange
    // DO NOT REMOVE UNTIL CAN DRAW SQUARE USING CLASS
    inline const char* FRAGMENT_SHADER_SOURCE{
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0"};

    inline const char* FRAGMENT_SHADER_SOURCE_FILENAME{
        "./Shaders/fragmentShaderSource.fs"};
    inline const char* FRAGMENT_SHADER_SOURCE_YELLOW_FILENAME{
        "./Shaders/fragmentShaderSourceYellow.fs"};

    inline const char* FRAGMENT_SHADER_TEXTURE_FILENAME{
        "./Shaders/fragmentShaderTexture.fs"};

    inline const char* FRAGMENT_SHADER_TEXTURE_TASK_ONE_FILENAME{
        "./Shaders/fragmentShaderTextureTaskOne.fs"};

    inline const char* FRAGMENT_SHADER_TEXTURE_UNIFORM_FILENAME{
        "./Shaders/fragmentShaderTextureUniform.fs"};

    // we specify three vertices
    // each of them with position in 3d space
    // x y z
    inline constexpr float TRIANGLE_VERTICES[]{
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
        };

    inline constexpr size_t TRIANGLE_VERTICES_SIZE = {sizeof(TRIANGLE_VERTICES)};

    inline constexpr unsigned int TRIANGLE_INDICES[]{
        0, 1, 2,  // first triangle
    };

    inline constexpr size_t TRIANGLE_INDICES_SIZE = {sizeof(TRIANGLE_INDICES)};

    inline constexpr float TRIANGLES_VERTICES[]{
        // first triangle
        -0.9f, -0.5f, 0.0f,  // left
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top
                            // second triangle
        0.0f, -0.5f, 0.0f,   // left
        0.9f, -0.5f, 0.0f,   // right
        0.45f, 0.5f, 0.0f    // top
    };

    inline constexpr size_t TRIANGLES_VERTICES_SIZE = {sizeof(TRIANGLES_VERTICES)};

    inline constexpr unsigned int TRIANGLES_INDICES[]{
        0, 1, 2,  // first triangle
        0, 1, 2   // second triangle
    };

    inline constexpr size_t TRIANGLES_INDICES_SIZE = {sizeof(TRIANGLES_INDICES)};

    inline constexpr float TRIANGLE_ONE[]{
        // first triangle
        -0.9f,  -0.5f, 0.0f,  // left
        -0.0f,  -0.5f, 0.0f,  // right
        -0.45f, 0.5f,  0.0f,  // top
    };

    inline constexpr size_t TRIANGLE_ONE_SIZE = {sizeof(TRIANGLE_ONE)};

    inline constexpr float TRIANGLE_TWO[]{
        // second triangle
        0.0f,  -0.5f, 0.0f,  // left
        0.9f,  -0.5f, 0.0f,  // right
        0.45f, 0.5f,  0.0f   // top
    };

    inline constexpr size_t TRIANGLE_TWO_SIZE = {sizeof(TRIANGLE_TWO)};

    inline constexpr float TRIANGLE_COLORS[]{
        // positions         // colors
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
        0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f   // top
    };

    inline constexpr size_t TRIANGLE_COLORS_SIZE = {sizeof(TRIANGLE_COLORS)};

    // compare with square done with only vertices:
    /*
    float vertices[] = {
    // first triangle
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f,  // top left
    // second triangle
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
    };
    bottom right and top left is specified twice !
    */
    inline constexpr float SQUARE_VERTICES[]{
        0.5f,   0.5f,  0.0f,  // top right
        0.5f,   -0.5f, 0.0f,  // bottom right
        -0.25f, -0.5f, 0.0f,  // bottom left
        -0.25f, 0.5f,  0.0f   // top left
    };

    inline constexpr unsigned int SQUARE_INDICES[]{
        0, 1, 3,  // first triangle
        1, 2, 3,  // second triangle
    };

    inline constexpr size_t SQUARE_INDICES_SIZE = {sizeof(SQUARE_INDICES)};

    inline constexpr size_t SQUARE_VERTICES_SIZE = {sizeof(SQUARE_VERTICES)};

    inline constexpr int MAX_DRAW_CALL = {15};

    // https://learnopengl.com/img/getting-started/tex_coords.png
    inline constexpr float TEXTURE_VERTICES[]{
        // positions            // colors           // texture coords
        0.5f,  0.5f,  0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // top right
        0.5f,  -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // bottom left
        -0.5f, 0.5f,  0.0f,     1.0f, 1.0f, 0.0f,   0.0f, 1.0f   // top left
    };

    inline constexpr size_t TEXTURE_VERTICES_SIZE = {sizeof(TEXTURE_VERTICES)};

    inline constexpr float TEXTURE_VERTICES_2F[]{
        // positions            // colors           // texture coords
        0.5f,  0.5f,  0.0f,     1.0f, 0.0f, 0.0f,   2.0f, 2.0f,  // top right
        0.5f,  -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   2.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // bottom left
        -0.5f, 0.5f,  0.0f,     1.0f, 1.0f, 0.0f,   0.0f, 2.0f   // top left
    };

    inline constexpr size_t TEXTURE_VERTICES_2F_SIZE = {
        sizeof(TEXTURE_VERTICES_2F)};

    inline constexpr float TEXTURE_VERTICES_TASK_THREE[]{
        // positions            // colors           // texture coords
        0.5f,  0.5f,  0.0f,     1.0f, 0.0f, 0.0f,   0.55f, 0.55f,  // top right
        0.5f,  -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   0.55f, 0.45f,  // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.45f, 0.45f,  // bottom left
        -0.5f, 0.5f,  0.0f,     1.0f, 1.0f, 0.0f,   0.45f, 0.55f   // top left
    };

    inline constexpr size_t TEXTURE_VERTICES_TASK_THREE_SIZE = {
        sizeof(TEXTURE_VERTICES_TASK_THREE)};

    inline constexpr unsigned int TEXTURE_INDICES[]{
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    inline constexpr size_t TEXTURE_INDICES_SIZE = {sizeof(TEXTURE_INDICES)};
};  // namespace constants

#endif  // ENGINE_ENGINE_CONSTANTS_HPP_
