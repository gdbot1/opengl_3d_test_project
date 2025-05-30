#version 330

out vec4 fragColor;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 projection_matrix, view_matrix, module_matrix;

void main() {
    gl_Position = projection_matrix * view_matrix * module_matrix * vec4(position.xyz, 1);
    fragColor = vec4(color.rgb, 1);
}