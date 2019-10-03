#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 tex;

out vec3 FragPos;
out vec3 Normal;
out vec3 lightPos;
out vec2 texCoord;

uniform mat4 model;

void main()
{
    FragPos = vec3(model*vec4(aPos, 1.0));
    Normal = normalize(vec3(model* vec4(aNormal, 0.0)));
    gl_Position = vec4(FragPos, 1.0);
    texCoord = tex;
}