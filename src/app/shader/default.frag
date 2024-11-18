#version 330 core

out vec4 FragColor;

in vec2 texCoord;
in float shading_value;

uniform sampler2D tex;


void main() {
    vec4 texture_colour = texture(tex, texCoord);

    if (texture_colour.r == 0.0 && texture_colour.r == 0.0 && texture_colour.r == 0.0 ){
        discard;
    }
    FragColor = texture_colour * shading_value;
}