#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;

out vec3 light;
out vec3 normal;
out vec2 UV;

uniform mat4 transform;
uniform mat4 model;

void main()
{
    gl_Position = transform * model * vec4(aPos, 1.0);
    
    normal = aNormal;
    UV = aUV;
    light = vec3( clamp(dot(normal, vec3(0.0, 0.0, 1.0)), 0.0, 1.0) );
}
