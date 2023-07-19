#include "include/sln/type/texture.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <sln/glw/ShaderProgram.hpp>
#include <sln/glw/VertexBuffer.hpp>
#include <sln/glw/ElementBuffer.hpp>
#include <sln/glw/TextureBuffer.hpp>
#include <sln/glw/Shader.hpp>
#include <sln/collada_parser.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>
#include <vector>
#include <cmath>



namespace sln::glw {
class Instance {
public:
        Instance();
        ~Instance();
};

sln::glw::Instance::Instance() {
        glfwInit();
}
sln::glw::Instance::~Instance() {
        glfwTerminate();
}
}




namespace sln::glw {
class Window {
public:
        Window(int width, int height);

        operator GLFWwindow*() { return m_window; }
private:
        GLFWwindow* m_window;
        int m_width;
        int m_height;
};

sln::glw::Window::Window(int width, int height) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        m_window = glfwCreateWindow(width, height, "D05 OpenGL Ventures", nullptr, nullptr);
        glfwGetFramebufferSize(m_window, &m_width, &m_height);
        glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int w, int h){
                glViewport(0, 0, w, h);
        });
        glEnable(GL_MULTISAMPLE);
        if (m_window == nullptr)
                throw std::runtime_error("Failed to create window");
        glfwMakeContextCurrent(m_window);
        glfwSwapInterval(0);
        glewExperimental = true;
        if (glewInit() != GLEW_OK)
                throw std::runtime_error("Failed to initialize GLEW");
        std::cout << "Initialized GLEW " << glGetString(GL_VERSION) << '\n';
}
}



int main (int argc, char *argv[])
{
        sln::glw::Instance instance;
        sln::glw::Window window(720, 720);

        sln::Mesh suzanne = sln::parse_collada(argv[1]);

        sln::Texture diffuse(argv[2]);
        sln::Texture maps(argv[3]);

        uint32_t VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        sln::glw::VertexBuffer suz_vertices{suzanne.vertices};
        sln::glw::ElementBuffer suz_elements{suzanne.triangles};
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(sln::Vertex), (void*)(offsetof(sln::Vertex, position)));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(sln::Vertex), (void*)(offsetof(sln::Vertex, uv)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(sln::Vertex), (void*)(offsetof(sln::Vertex, normal)));
        glEnableVertexAttribArray(2);
        glEnable(GL_DEPTH_TEST);

        sln::glw::ShaderProgram shader_program{"../shaders/vertex.vert", "../shaders/fragment.frag"};
        shader_program.use();
        glUniform1i(glGetUniformLocation(shader_program, "diffuse"), 0);
        glUniform1i(glGetUniformLocation(shader_program, "maps"), 1);

        int max_attribs;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_attribs);
        std::cout << "Max vertex attributes: " << max_attribs << '\n';

        int transform_uniform_location = glGetUniformLocation(shader_program, "transform");
        int model_uniform_location = glGetUniformLocation(shader_program, "model");

        glm::mat4 transform_matrix{1.0f};
        glm::mat4 view_matrix{1.0f};
        glm::mat4 model_matrix{1.0f};
        glm::mat4 projection_matrix{1.0f};

        float prev_time = 0;
        float time = 0;
        float delta = 0;

        float rotation = 0;


        while(!glfwWindowShouldClose(window)) {
                time = glfwGetTime();
                delta = time-prev_time;
                prev_time = time;

                rotation += delta;
                model_matrix = /*glm::translate(glm::mat4{1.f}, {std::sin(time)*0.5f, 0.f, 0.f}) **/ glm::rotate(glm::mat4{1.f}, rotation, {0.f, 1.f, 0.f}) * 0.3f;
                //view_matrix = glm::translate(view_matrix, glm::vec3(0.f, 0.f, -3.f));
                //projection_matrix = glm::perspective(glm::radians(45.f), 1280.f/720.f, 0.1f, 100.f);

                transform_matrix = projection_matrix * view_matrix;

                glClearColor(0.07f, 0.07f, 0.09f, 1.f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                shader_program.use();
                glUniformMatrix4fv(transform_uniform_location, 1, false, reinterpret_cast<float*>(&transform_matrix)); 
                glUniformMatrix4fv(model_uniform_location, 1, false, reinterpret_cast<float*>(&model_matrix)); 
                suz_vertices.bind();
                suz_elements.bind();
                diffuse.bind(0);
                maps.bind(1);
                glDrawElements(GL_TRIANGLES, suzanne.triangles.size()*3, GL_UNSIGNED_INT, 0);

                glfwSwapBuffers(window);
                glfwPollEvents();
        }

        glfwTerminate();
        return 0;
}
