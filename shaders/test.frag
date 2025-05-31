#version 330

out vec4 exitColor;

in vec4 fragColor;
in vec2 fragTexCord;

uniform sampler2D tex;
uniform int texStatus;

void main() {
    vec4 texColor = texStatus == 0 ? vec4(1, 1, 1, 1) : texture(tex, fragTexCord);

    exitColor = fragColor * texColor;
}