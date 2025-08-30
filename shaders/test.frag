#version 330

out vec4 exitColor;

in vec4 fragColor;
in vec4 fragGlobalPos;
in vec2 fragTexCord;

uniform sampler2D tex;
uniform int texStatus;

struct TestStruct {
    float far;
    vec3 position, color;
};
uniform TestStruct val;

uniform sampler2D texture_val;

uniform vec3 colour[3];

void main() {
    vec4 texColor = texStatus == 0 ? vec4(1, 1, 1, 1) : texture(texture_val, fragTexCord);

    float dist_factor = 1 - clamp(length(fragGlobalPos.xyz - val.position) / val.far, 0, 1);

    exitColor = fragColor * texColor * vec4(val.color, 1.0f) * vec4(vec3(dist_factor), 1.0f);
}