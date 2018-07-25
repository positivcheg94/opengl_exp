#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include <ogl/ogl.hpp>

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

const char* vertex_shader_code =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"out vec4 outColor;"
"\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   outColor    = vec4(aColor, 1.f);"
"}\n";

const char* fragment_shader_code =
"#version 330 core\n"
"in vec4 outColor;"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"   FragColor = outColor;\n"
"}\n";

float get_01(float in)
{
    return in - std::floor(in);
}

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    
    auto vertice_buffer = ogl::Buffer::create(ogl::BufferType::Array        , ogl::Float, vertices  , sizeof(vertices)  , ogl::UsageHint::StaticDraw);
    auto index_buffer   = ogl::Buffer::create(ogl::BufferType::ElementArray , ogl::UInt , indices   , sizeof(indices)   , ogl::UsageHint::StaticDraw);
    auto vao            = ogl::ArrayBuffer::create({{ vertice_buffer, { { 0, 3, ogl::True, 8, 0 }, { 1, 3, ogl::True, 8, 3 },{ 2, 2, ogl::True, 8, 6 } } }}, index_buffer);

    auto v_shader       = ogl::Shader::create(ogl::ShaderType::Vertex   , std::string(vertex_shader_code)   , false);
    auto f_shader       = ogl::Shader::create(ogl::ShaderType::Fragment , std::string(fragment_shader_code) , false);
    auto program        = ogl::Program::create(v_shader, f_shader);



    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        program->activate();
        vao->activate();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        vao->deactivate();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

