#version 430

layout(location = 0) in vec2 inUV;
layout(location = 0) out vec3 outColor;

uniform layout(binding = 0) sampler2D s_Image;

uniform float u_Filter[9];
uniform vec2 u_PixelSize;

void main() {

    outColor = texture(s_Image, uv);
}
