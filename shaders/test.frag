#version 330

out vec4 exitColor;

in vec4 fragColor;

void main() {
    exitColor = fragColor;
}