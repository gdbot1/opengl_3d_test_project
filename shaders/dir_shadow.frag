#version 330

out vec4 exitColor;

in vec4 fragPos;

void main() {
    float depth = clamp(fragPos.z / fragPos.w * 0.5f + 0.5f, 0, 1);

    gl_FragDepth = depth;
}
