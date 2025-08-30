#version 330

out vec4 fragColor;
out vec4 fragGlobalPos;
out vec2 fragTexCord;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCord;

uniform mat4 projection_matrix, view_matrix, model_matrix;

void main() {
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position.xyz, 1);
    fragGlobalPos = model_matrix * vec4(position.xyz, 1);
    fragColor = vec4(color.rgb, 1);
    fragTexCord = texCord;
}