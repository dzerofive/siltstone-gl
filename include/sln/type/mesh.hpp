#pragma once

#include <glm/vec3.hpp>
#include <glm/integer.hpp>
#include <glm/vec2.hpp>
#include <vector>

namespace sln {
struct Vertex {
        glm::vec3 position;
        glm::vec2 uv;
        glm::vec3 normal;
};
class Mesh {
public:
        std::vector<sln::Vertex> vertices;
        std::vector<glm::uvec3> triangles;
};
}
