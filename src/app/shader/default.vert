#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 camMatrix;
uniform vec3 position;

void main() {
    gl_Position = camMatrix * vec4(aPos + position, 1.0);
    texCoord = aTexCoord;
}