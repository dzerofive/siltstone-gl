#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>


namespace sln::glw {
class TextureBuffer {
public:
        TextureBuffer() {};
        TextureBuffer(const uint8_t* texture_data, uint32_t width, uint32_t height);
        operator GLuint();
        void bind(int texture_index = 0);
private:
        uint32_t m_texture;
};

void sln::glw::TextureBuffer::bind(int texture_index) {
        glActiveTexture(GL_TEXTURE0 + texture_index);
        glBindTexture(GL_TEXTURE_2D, m_texture);
}
sln::glw::TextureBuffer::operator GLuint() {
        return m_texture;
}
sln::glw::TextureBuffer::TextureBuffer(const uint8_t* texture_data, uint32_t width, uint32_t height) {
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
        glGenerateMipmap(GL_TEXTURE_2D);
}
}
