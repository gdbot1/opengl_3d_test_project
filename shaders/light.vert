#version 330

#define MAX_DIR_LIGHTS 10

struct DirLight {
    vec3 color;
    vec4 pixel_normal, pixel_position;
};

out vec4 fragGlobalPos;
out vec4 fragGlobalNormal;
out vec4 fragColor;
out vec4 fragNormal;
out vec2 fragTexCord;
out mat3 tbn;
out mat3 i_tbn;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 texCord;
layout(location = 4) in vec3 tangent;
layout(location = 5) in vec3 bitangent;

uniform mat4 projection_matrix, view_matrix, model_matrix;
uniform mat4 shadow_projection_matrix, shadow_view_matrix;

void main() {
    mat4 camera_matrix = projection_matrix * view_matrix;
    mat4 light_matrix = shadow_projection_matrix * shadow_view_matrix;

    mat4 matrix = camera_matrix * model_matrix;

    gl_Position = matrix * vec4(position, 1);
    fragNormal = matrix * vec4(normal, 0);

    fragGlobalPos = model_matrix * vec4(position, 1);
    fragGlobalNormal = model_matrix * vec4(normal, 0);

    fragTexCord = texCord;
    fragColor = vec4(color.rgb, 1);

    vec3 tang = normalize(vec4(model_matrix * vec4(tangent, 0)).xyz);
    vec3 bitang = normalize(vec4(model_matrix * vec4(bitangent, 0)).xyz);

    tbn = mat3(tang, bitang, normalize(fragGlobalNormal.xyz));
    i_tbn = inverse(tbn);
}