#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <sln/type/mesh.hpp>
#include <vector>


namespace sln::glw {
class VertexBuffer {
public:
        VertexBuffer(const std::vector<sln::Vertex>& vertex_array);
        operator GLuint();
        void bind();
private:
        uint32_t m_vbo;
};

void sln::glw::VertexBuffer::bind() {
        glBindVertexArray(m_vbo);
}
sln::glw::VertexBuffer::operator GLuint() {
        return m_vbo;
}
sln::glw::VertexBuffer::VertexBuffer(const std::vector<sln::Vertex>& vertex_array) {
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, vertex_array.size()*sizeof(vertex_array[0]), vertex_array.data(), GL_STATIC_DRAW);
}
}
