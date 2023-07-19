#version 330 core
out vec4 FragColor;

in vec3 light;
in vec3 normal;
in vec2 UV;

uniform sampler2D diffuse;
uniform sampler2D maps;

void main()
{
    vec3 color = texture(diffuse, UV).rgb*0.5 + vec3(2.0, 0.5, 0.2)*light*texture(maps, UV).rrr - texture(maps, UV).bbb;

    //color = color / (color + vec3(1.0));
    //color = pow(color, vec3(1.0/2.2));

    FragColor = vec4(color.xyz, 1.0);
} 
