#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include <vector>


namespace sln::glw {
class ElementBuffer {
public:
        ElementBuffer(const std::vector<glm::uvec3>& element_array);
        operator GLuint();
        void bind();
private:
        uint32_t m_ebo;
};

void sln::glw::ElementBuffer::bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
}
sln::glw::ElementBuffer::operator GLuint() {
        return m_ebo;
}
sln::glw::ElementBuffer::ElementBuffer(const std::vector<glm::uvec3>& element_array) {
        glGenBuffers(1, &m_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_array.size()*sizeof(element_array[0]), element_array.data(), GL_STATIC_DRAW);
}
}
