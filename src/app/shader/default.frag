#version 330 core

out vec4 FragColor;

in vec2 texCoord;
in float shading_value;

uniform sampler2D tex;


void main() {
    FragColor = texture(tex, texCoord) * shading_value;
}