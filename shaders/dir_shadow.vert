#version 330

out vec4 fragPos;

layout(location = 0) in vec3 position;

uniform mat4 projection_matrix, view_matrix, model_matrix;

void main() {
    fragPos = projection_matrix * view_matrix * model_matrix * vec4(position.xyz, 1);
    gl_Position = fragPos;
}
