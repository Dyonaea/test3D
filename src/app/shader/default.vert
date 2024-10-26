#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in float aShading_value;

out vec2 texCoord;
out float shading_value;

uniform mat4 camMatrix;

void main() {
    gl_Position = camMatrix * vec4(aPos, 1.0);
    texCoord = aTexCoord;
    shading_value = aShading_value;
}