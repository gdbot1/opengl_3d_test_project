#version 330

out vec3 fragPos;

layout(location = 0) in vec3 position;

uniform mat4 projection_matrix, view_matrix, model_matrix;

void main() {
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position.xyz, 1);
    //gl_Position.x *= -1;
    fragPos = vec3(model_matrix * vec4(position.xyz, 1));
}