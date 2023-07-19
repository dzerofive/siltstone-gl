#pragma once

#include <GL/glew.h>

#include <filesystem>
#include <iostream>
#include <fstream>


namespace sln::glw {


class Shader {
public:
        enum Type {
                vertex = GL_VERTEX_SHADER,
                fragment = GL_FRAGMENT_SHADER
        };
        Shader(std::filesystem::path source_path, sln::glw::Shader::Type shader_type);
        ~Shader();
        operator GLuint();

private:
        uint32_t m_shader;
};
} // namespace sln::glw

sln::glw::Shader::Shader(std::filesystem::path source_path, sln::glw::Shader::Type shader_type) {
        m_shader = glCreateShader(shader_type);

        std::ifstream src_file(source_path, std::ios::in);
        if(!src_file.is_open())
                std::runtime_error("SHADER ERROR :: Failed to open shader source");
        std::string source(std::istreambuf_iterator<char>{src_file}, {});
        auto code = source.c_str();
        glShaderSource(m_shader, 1, &code, nullptr);
        glCompileShader(m_shader);

        int success;
        char info_log[512];
        glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
        if(!success) {
                glGetShaderInfoLog(m_shader, 512, nullptr, info_log);
                std::cout << "SHADER ERROR :: " << info_log << '\n';
        }
}

sln::glw::Shader::~Shader() {
        glDeleteShader(m_shader);
}

sln::glw::Shader::operator GLuint() {
        return m_shader;
}
