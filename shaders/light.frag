#version 330

#define MAX_POINT_LIGHTS 10
#define MAX_DIR_LIGHTS 10

out vec4 exitColor;

in vec4 fragGlobalPos;
in vec4 fragGlobalNormal;
in vec4 fragColor;
in vec4 fragNormal;
in vec2 fragTexCord;
in mat3 tbn;
in mat3 i_tbn;

uniform bool hasTex;
uniform sampler2D tex;

uniform bool hasNormTex;
uniform sampler2D norm_tex;

uniform bool hasParalTex;
uniform sampler2D paral_tex;

uniform vec3 cameraPos;

struct PointLight {
    int width, height;
    float far;
    vec3 position, color;

    samplerCube shadow_map;
};

struct DirLight {
    int width, height;
    mat4 matrix;
    vec3 color;

    sampler2D shadow_map;
};

uniform PointLight point_light[MAX_POINT_LIGHTS];
uniform DirLight dir_light[MAX_DIR_LIGHTS];

uniform int dir_lights, point_lights;

uniform float material_glare;

bool isPointLighted(vec3 pixel_light, float far, samplerCube shadow_map, float bias) {
    float dist = length(pixel_light);

    float depth = clamp(dist / far, 0, 1);

    vec3 cube_vec = vec3(pixel_light.x, -pixel_light.y, pixel_light.z);

    return depth < texture(shadow_map, cube_vec).r - bias;
}

bool isPointLighted(vec3 pixel_light, float far, samplerCube shadow_map, float s_x, float s_y, float bias) {
    float dist = length(pixel_light);

    float depth = clamp(dist / far, 0, 1);

    vec3 cube_vec = vec3(pixel_light.x, -pixel_light.y, pixel_light.z);

    vec3 abs_cube_vec = abs(cube_vec);

    float MAX_COMP = max(max(abs_cube_vec.x, abs_cube_vec.y), abs_cube_vec.z);//max component

    cube_vec /= MAX_COMP;

    int max_value_status = MAX_COMP == abs_cube_vec.x ? 0 : (MAX_COMP == abs_cube_vec.y ? 1 : 2);//x - 1, y - 2, z - 3

    switch (max_value_status) {
        case 0:
            return depth < texture(shadow_map, normalize(vec3(cube_vec.x, cube_vec.y + s_y, cube_vec.z + s_x))).r - bias;
        case 1:
            return depth < texture(shadow_map, normalize(vec3(cube_vec.x + s_x, cube_vec.y, cube_vec.z + s_y))).r - bias;
        default:
            return depth < texture(shadow_map, normalize(vec3(cube_vec.x + s_x, cube_vec.y + s_y, cube_vec.z))).r - bias;
    }
}

//pixel_light_pos - pixel position in light space
bool isDirLighted(vec4 pixel_light_pos, sampler2D shadow_map, float bias) {
    vec3 pos = (pixel_light_pos.xyz / pixel_light_pos.w) * 0.5f + 0.5f;

    float depth = texture(shadow_map, pos.xy).r;

    return pos.z < depth - bias;
}

bool isDirLighted(vec4 pixel_light_pos, sampler2D shadow_map, float s_x, float s_y, float bias) {
    vec3 pos = (pixel_light_pos.xyz / pixel_light_pos.w) * 0.5f + 0.5f;

    float depth = texture(shadow_map, vec2(pos.x + s_x, pos.y + s_y)).r;

    return pos.z < depth - bias;
}

vec3 addColor(vec3 main_color, vec3 support_color, float light) {
    return main_color + support_color * light;
}

float getGlaresFactor(float cosB, float glare) {
    return pow(clamp(cosB, 0, 1), 1 / glare) * (1 - glare) + 1;
}

float getDistFactor(float dist, float far) {
    return 1 - clamp(dist / far, 0, 1);
}

float getAngleFactor(float cosL, int c) {
    return 1 - pow(1 - clamp(cosL, 0, 1), c);
}

float getPointShadowFactor(vec3 pixel_light, float far, samplerCube shadow_map, float bias) {
    return isPointLighted(pixel_light, far, shadow_map, bias) ? 1 : 0;
}

float getPointSoftShadowFactor(vec3 pixel_light, float far, samplerCube shadow_map, int s_width, int s_height, float focus, float bias) {
    float t_x = 1.0f / s_width * focus, t_y = 1.0f / s_height * focus;

    int lighted = 0, count = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            count++;

            if (isPointLighted(pixel_light, far, shadow_map, t_x * j, t_y * i, bias)) {
                lighted++;
            }
        }
    }

    return float(lighted) / float(count);
}

float getDirSoftShadowFactor(vec4 pixel_light_pos, sampler2D shadow_map, int s_width, int s_height, float focus, float bias) {
    float t_x = 1.0f / s_width * focus, t_y = 1.0f / s_height * focus;

    int lighted = 0, count = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            count++;

            if (isDirLighted(pixel_light_pos, shadow_map, t_x * j, t_y * i, bias)) {
                lighted++;
            }
        }
    }

    return float(lighted) / float(count);
}

float getDirShadowFactor(vec4 pixel_light_pos, sampler2D shadow_map, float bias) {
    return isDirLighted(pixel_light_pos, shadow_map, bias) ? 1 : 0;
}

//cosB - cos of angle between reflected light and canera (for glares, where 1 - light lighting in eye, 0 - light fully perpendicular).
float getCosB(vec3 pixel_light, vec3 global_pixel_normal, vec3 pixel_camera) {
    vec3 reflect_pixel_light = reflect(normalize(pixel_light), normalize(global_pixel_normal));

    return dot(reflect_pixel_light, pixel_camera) / (length(reflect_pixel_light) * length(pixel_camera));//cosB
}

//cosL - cos of angle between light and normal of pixel (frag)
float getCosL(vec3 pixel_light, vec3 normal) {
    return dot(normal, pixel_light) / (length(normal) * length(pixel_light));
}

vec3 pointLightProcessing(vec3 lightColor, vec3 pixel_light, vec3 pixel_camera, vec3 normal, float far, vec3 color, samplerCube shadow_map, int width, int height, float material_glare) {
    float dist = length(pixel_light);

    float dist_factor = getDistFactor(dist, far);

    if (dist_factor == 0) {
        return lightColor;
    }

    vec3 cube_vec = vec3(pixel_light.x, -pixel_light.y, pixel_light.z);

    //float shadow_factor = getPointShadowFactor(pixel_light, far, shadow_map, 0.001f);
    float shadow_factor = getPointSoftShadowFactor(pixel_light, far, shadow_map, width, height, 8, 0.001f);

    if (shadow_factor == 0) {
        return lightColor;
    }

    float cosL = getCosL(pixel_light, normal);

    float angle_factor = getAngleFactor(cosL, 1);

    if (angle_factor == 0) {
        return lightColor;
    }

    float cosB = getCosB(pixel_light, normal, pixel_camera);

    float glares_factor = getGlaresFactor(cosB, material_glare);

    float light = dist_factor * angle_factor * shadow_factor * glares_factor;

    return addColor(lightColor, color, light);
}

vec3 dirLightProcessing(vec3 lightColor, vec3 global_pixel_position, vec3 global_pixel_normal, vec3 camera_position, mat4 matrix, sampler2D shadow_map, vec3 color, int width, int height, float material_glare) {
    vec4 pixel_light_position = vec4(matrix * vec4(global_pixel_position, 1));
    vec4 pixel_light_normal = vec4(matrix * vec4(global_pixel_normal, 0));

    vec4 camera_light_position = vec4(matrix * vec4(camera_position, 1));

    vec3 pixel_camera_light_position = pixel_light_position.xyz - camera_light_position.xyz;

    float shadow_factor = getDirSoftShadowFactor(pixel_light_position, shadow_map, width, height, 1, 0.001f);

    if (shadow_factor == 0) {
        return lightColor;
    }

    float cosL = getCosL(vec3(0, 0, -1), pixel_light_normal.xyz);

    float angle_factor = getAngleFactor(cosL, 1);

    if (angle_factor == 0) {
        return lightColor;
    }

    float cosB = getCosB(vec3(0, 0, -1), pixel_light_normal.xyz, pixel_camera_light_position.xyz);

    float glares_factor = getGlaresFactor(cosB, material_glare);

    float light = angle_factor * shadow_factor * glares_factor;

    return addColor(lightColor, color, light);
}

void main() {
    vec3 pixel_camera = fragGlobalPos.xyz - cameraPos;

    vec2 uv = fragTexCord.xy;

    if (hasParalTex) {
        vec3 camera_dir = normalize(tbn * (-pixel_camera));
        //vec3 camera_dir = normalize(i_tbn * cameraPos - vec3(uv, 0.0f));

        if (camera_dir.z != 0) {
            float heightScale = 0.05f;
            const float minLayers = 8.0f;
            const float maxLayers = 32.0f;
            float layers = mix(maxLayers, minLayers, abs(dot(vec3(0, 0, 1), camera_dir)));

            float layerDepth = 1.0f / layers;

            vec2 deltaUV = camera_dir.xy / camera_dir.z * heightScale / layers;

            float currentDepth = 0.0f;

            float depthOfTheMap = 1.0f - texture(paral_tex, uv).r;

            float i = layers;

            while (currentDepth < depthOfTheMap && i > 0) {
                i -= 1;
                uv -= deltaUV;
                currentDepth += layerDepth;

                depthOfTheMap = 1.0f - texture(paral_tex, uv).r;
            }

            vec2 prevTextCoords = uv + deltaUV;
            float afterDepth = depthOfTheMap - currentDepth;
            float beforeDepth = 1.0f - texture(paral_tex, prevTextCoords).r - currentDepth + layerDepth;
            float weight = afterDepth / (afterDepth - beforeDepth);
            uv = prevTextCoords * weight + uv * (1.0f - weight);
        }
    }

    vec3 normal = fragGlobalNormal.xyz;

    if (hasNormTex) {
        normal = tbn * (texture(norm_tex, uv).xyz * 2.0f - 1.0f);
    }

    vec4 texColor = vec4(1);

    if (hasTex) {
        texColor = texture(tex, uv);
    }

    vec3 lightColor = vec3(0);

    for (int i = 0; i < point_lights; i++) {
        vec3 pixel_light = point_light[i].position - fragGlobalPos.xyz;

        lightColor = pointLightProcessing(lightColor, pixel_light, pixel_camera, normal, point_light[i].far, point_light[i].color, point_light[i].shadow_map, point_light[i].width, point_light[i].height, material_glare);
    }

    for (int i = 0; i < dir_lights; i++) {
        lightColor = dirLightProcessing(lightColor, fragGlobalPos.xyz, normal, cameraPos, dir_light[i].matrix, dir_light[i].shadow_map, dir_light[i].color, dir_light[i].width, dir_light[i].height, material_glare);
    }

    exitColor = vec4(fragColor.rgb * (lightColor * 0.8f + 0.2f), 1) * texColor;
}