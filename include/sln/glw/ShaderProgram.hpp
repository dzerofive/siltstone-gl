#pragma once

#include <GL/glew.h>
#include "Shader.hpp"

#include <iostream>
#include <filesystem>

namespace sln::glw {
class ShaderProgram {
public:
        ShaderProgram(sln::glw::Shader vertex_shader, 
                      sln::glw::Shader fragment_shader);
        ShaderProgram(std::filesystem::path vertex_source_path,
                      std::filesystem::path fragment_source_path);

        void use();
        operator GLuint();

private:
        uint32_t m_shader_program;
};
} // namespace sln::glw



inline void check_shader_status(uint32_t shader_program) {
        int success;
        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if(!success) {
                char info_log[512];
                glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
        }
        std::cout << "Created shader program\n";
}
void sln::glw::ShaderProgram::use() {
        glUseProgram(m_shader_program);
}

sln::glw::ShaderProgram::ShaderProgram(std::filesystem::path vertex_source_path,
                                       std::filesystem::path fragment_source_path) {
        sln::glw::Shader vert(vertex_source_path, sln::glw::Shader::Type::vertex);
        sln::glw::Shader frag(fragment_source_path, sln::glw::Shader::Type::fragment);
        m_shader_program = glCreateProgram();
        glAttachShader(m_shader_program, vert);
        glAttachShader(m_shader_program, frag);
        glLinkProgram(m_shader_program);
        check_shader_status(m_shader_program);
}

sln::glw::ShaderProgram::ShaderProgram(
        sln::glw::Shader vertex_shader, 
        sln::glw::Shader fragment_shader) {
        m_shader_program = glCreateProgram();
        glAttachShader(m_shader_program, vertex_shader);
        glAttachShader(m_shader_program, fragment_shader);
        glLinkProgram(m_shader_program);
        check_shader_status(m_shader_program);
}
sln::glw::ShaderProgram::operator GLuint() {
        return m_shader_program;
}
