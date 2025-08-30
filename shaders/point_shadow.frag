#version 330

out vec4 exitColor;

in vec3 fragPos;

uniform vec3 lightPos;
uniform float far;

void main() {
    float depth = clamp(length(fragPos - lightPos) / far, 0, 1);

    //float depth = clamp(fragPos.z / fragPos.w * 0.5f + 0.5f, 0, 1);

    gl_FragDepth = depth;
}