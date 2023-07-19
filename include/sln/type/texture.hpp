#pragma once

#include <sln/glw/TextureBuffer.hpp>
#include <stb_image.h>

#include <filesystem>
#include <iostream>

namespace sln {
class Texture {
public:
        Texture(std::filesystem::path texture_path) {
                int width, height, channels;
                uint8_t* data = stbi_load(texture_path.c_str(), &width, &height, &channels, 0);
                if(!data) throw std::runtime_error("Failed to load texture file");

                std::cout << "Loaded texture " << texture_path.filename() << '\n';

                m_texture_buffer = sln::glw::TextureBuffer(data, width, height);
                stbi_image_free(data);
        }
        void bind(int texture_index = 0) {
                m_texture_buffer.bind(texture_index);
        }
private:
        sln::glw::TextureBuffer m_texture_buffer = {};
};
} // namespace sln
