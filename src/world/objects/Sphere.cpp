#include "Sphere.h"

#include <iostream>

#define PI 3.14159265358979323846f

Sphere::Sphere(float x, float y, float z, float radius, int segments, int stacks) : Object(createSphere(x, y, z, radius, segments, stacks)) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->radius = radius;
    this->segments = segments;
    this->stacks = stacks;
}

glm::vec3 Sphere::getPosition() const {
    return glm::vec3(x, y, z);
}

float Sphere::getRadius() const {
    return radius;
}

glm::vec2 Sphere::getDimension() const {
    return glm::vec2(segments, stacks);
}

std::shared_ptr<VAO> Sphere::createSphere(float x, float y, float z, float radius, int segments, int stacks) {
    float delta_segments = PI * 2 / segments;
    float delta_stacks = PI / stacks;

    std::vector<float> vertices;
    std::vector<float> color;
    std::vector<float> tx;
    std::vector<int> elements;

    for (int i = 0; i < segments; i++) {
	for (int j = 0; j < stacks; j++) {
	    int i2 = i + 1, j2 = j + 1;

	    glm::vec3 point_ij = math::spin(i * delta_segments, j * delta_stacks, radius);
	    glm::vec3 point_i2j = math::spin(i2 * delta_segments, j * delta_stacks, radius);
	    glm::vec3 point_i2j2 = math::spin(i2 * delta_segments, j2 * delta_stacks, radius);
	    glm::vec3 point_ij2 = math::spin(i * delta_segments, j2 * delta_stacks, radius);

	    vertices.push_back(point_ij.x);
	    vertices.push_back(point_ij.y);
	    vertices.push_back(point_ij.z);

	    tx.push_back(0);
	    tx.push_back(0);

	    vertices.push_back(point_i2j.x);
	    vertices.push_back(point_i2j.y);
	    vertices.push_back(point_i2j.z);

	    tx.push_back(0);
	    tx.push_back(0);

	    vertices.push_back(point_i2j2.x);
	    vertices.push_back(point_i2j2.y);
	    vertices.push_back(point_i2j2.z);

	    tx.push_back(0);
	    tx.push_back(0);

	    vertices.push_back(point_ij2.x);
	    vertices.push_back(point_ij2.y);
	    vertices.push_back(point_ij2.z);

	    tx.push_back(0);
	    tx.push_back(0);

	    float redC = point_ij.x / 2 + 0.5f;
	    float greenC = point_ij.y / 2 + 0.5f;
	    float blueC = point_ij.z / 2 + 0.5f;
	    
	    float red = std::max(0.0f, redC + 1.0f - (greenC + blueC));
	    float green = std::max(0.0f, greenC + 1.0f - (redC + blueC));
	    float blue = std::max(0.0f, blueC + 1.0f - (greenC + redC));

	    color.push_back(red);
	    color.push_back(green);
	    color.push_back(blue);

	    redC = point_i2j.x / 2 + 0.5f;
	    greenC = point_i2j.y / 2 + 0.5f;
	    blueC = point_i2j.z / 2 + 0.5f;
	    
	    red = std::max(0.0f, redC + 1.0f - (greenC + blueC));
	    green = std::max(0.0f, greenC + 1.0f - (redC + blueC));
	    blue = std::max(0.0f, blueC + 1.0f - (greenC + redC));

	    color.push_back(red);
	    color.push_back(green);
	    color.push_back(blue);

	    redC = point_i2j2.x / 2 + 0.5f;
	    greenC = point_i2j2.y / 2 + 0.5f;
	    blueC = point_i2j2.z / 2 + 0.5f;
	    
	    red = std::max(0.0f, redC + 1.0f - (greenC + blueC));
	    green = std::max(0.0f, greenC + 1.0f - (redC + blueC));
	    blue = std::max(0.0f, blueC + 1.0f - (greenC + redC));

	    color.push_back(red);
	    color.push_back(green);
	    color.push_back(blue);

	    redC = point_ij2.x / 2 + 0.5f;
	    greenC = point_ij2.y / 2 + 0.5f;
	    blueC = point_ij2.z / 2 + 0.5f;
	    
	    red = std::max(0.0f, redC + 1.0f - (greenC + blueC));
	    green = std::max(0.0f, greenC + 1.0f - (redC + blueC));
	    blue = std::max(0.0f, blueC + 1.0f - (greenC + redC));

	    color.push_back(red);
	    color.push_back(green);
	    color.push_back(blue);

            elements.push_back((i * stacks + j) * 4);
            elements.push_back((i * stacks + j) * 4 + 1);
            elements.push_back((i * stacks + j) * 4 + 2);
            elements.push_back((i * stacks + j) * 4);
            elements.push_back((i * stacks + j) * 4 + 2);
            elements.push_back((i * stacks + j) * 4 + 3);
	}
    }

    std::cout << "SPHERE VERTICES: " << vertices.size() << " s" << segments << " s" << stacks << std::endl;

    return make_shared<VAO_E>(std::vector<std::shared_ptr<VBO>>{
	make_shared<VBO>(vertices, 3),
	make_shared<VBO>(color, 3),
	make_shared<VBO>(tx, 2)
    }, make_shared<EBO>(elements), static_cast<int>(elements.size()));
}

/*
std::shared_ptr<VAO> Sphere::createSphere(float x, float y, float z, float radius, int segments, int stack) {
    float delta_segments = PI * 2 / segments;
    float delta_stacks = PI / stacks;

    std::vector<float> vertices(segments * stacks * 4 * 3);
    std::vector<float> color(segments * stacks * 4 * 3);
    std::vector<int> elements(segments * stacks * 6);

    for (int i = 0; i < segments; i++) {
	for (int j = 0; j < stacks; j++) {
	    int i2 = i + 1, j2 = j + 1;

	    glm::vec3 point_ij = math::spin(i * delta_segments, j * delta_stacks, radius);
	    glm::vec3 point_i2j = math::spin(i2 * delta_segments, j * delta_stacks, radius);
	    glm::vec3 point_i2j2 = math::spin(i2 * delta_segments, j2 * delta_stacks, radius);
	    glm::vec3 point_ij2 = math::spin(i * delta_segments, j2 * delta_stacks, radius);

	    vertices[(i * stacks + j) * 4 * 3] = point_ij.x;
	    vertices[(i * stacks + j) * 4 * 3 + 1] = point_ij.y;
	    vertices[(i * stacks + j) * 4 * 3 + 2] = point_ij.z;

	    vertices[(i * stacks + j) * 4 * 3 + 3] = point_i2j.x;
	    vertices[(i * stacks + j) * 4 * 3 + 4] = point_i2j.y;
	    vertices[(i * stacks + j) * 4 * 3 + 5] = point_i2j.z;

	    vertices[(i * stacks + j) * 4 * 3 + 6] = point_i2j2.x;
	    vertices[(i * stacks + j) * 4 * 3 + 7] = point_i2j2.y;
	    vertices[(i * stacks + j) * 4 * 3 + 8] = point_i2j2.z;

	    vertices[(i * stacks + j) * 4 * 3 + 9] = point_ij2.x;
	    vertices[(i * stacks + j) * 4 * 3 + 10] = point_ij2.y;
	    vertices[(i * stacks + j) * 4 * 3 + 11] = point_ij2.z;

	    float redC = point_ij.x / 2 + 0.5f;
	    float greenC = point_ij.y / 2 + 0.5f;
	    float blueC = point_ij.z / 2 + 0.5f;
	    
	    float red = std::max(0.0f, redC + 1.0f - (greenC + blueC));
	    float green = std::max(0.0f, greenC + 1.0f - (redC + blueC));
	    float blue = std::max(0.0f, blueC + 1.0f - (greenC + redC));

	    color[(i * stacks + j) * 4 * 3] = red;
	    color[(i * stacks + j) * 4 * 3 + 1] = green;
	    color[(i * stacks + j) * 4 * 3 + 2] = blue;

	    redC = point_i2j.x / 2 + 0.5f;
	    greenC = point_i2j.y / 2 + 0.5f;
	    blueC = point_i2j.z / 2 + 0.5f;
	    
	    red = std::max(0.0f, redC + 1.0f - (greenC + blueC));
	    green = std::max(0.0f, greenC + 1.0f - (redC + blueC));
	    blue = std::max(0.0f, blueC + 1.0f - (greenC + redC));

	    color[(i * stacks + j) * 4 * 3 + 3] = red;
	    color[(i * stacks + j) * 4 * 3 + 4] = green;
	    color[(i * stacks + j) * 4 * 3 + 5] = blue;

	    redC = point_i2j2.x / 2 + 0.5f;
	    greenC = point_i2j2.y / 2 + 0.5f;
	    blueC = point_i2j2.z / 2 + 0.5f;
	    
	    red = std::max(0.0f, redC + 1.0f - (greenC + blueC));
	    green = std::max(0.0f, greenC + 1.0f - (redC + blueC));
	    blue = std::max(0.0f, blueC + 1.0f - (greenC + redC));

	    color[(i * stacks + j) * 4 * 3 + 6] = red;
	    color[(i * stacks + j) * 4 * 3 + 7] = green;
	    color[(i * stacks + j) * 4 * 3 + 8] = blue;

	    redC = point_ij2.x / 2 + 0.5f;
	    greenC = point_ij2.y / 2 + 0.5f;
	    blueC = point_ij2.z / 2 + 0.5f;
	    
	    red = std::max(0.0f, redC + 1.0f - (greenC + blueC));
	    green = std::max(0.0f, greenC + 1.0f - (redC + blueC));
	    blue = std::max(0.0f, blueC + 1.0f - (greenC + redC));

	    color[(i * stacks + j) * 4 * 3 + 9] = red;
	    color[(i * stacks + j) * 4 * 3 + 10] = green;
	    color[(i * stacks + j) * 4 * 3 + 11] = blue;

            elements[(i * stacks + j) * 6] = (i * stacks + j) * 4;
            elements[(i * stacks + j) * 6 + 1] = (i * stacks + j) * 4 + 1;
            elements[(i * stacks + j) * 6 + 2] = (i * stacks + j) * 4 + 2;
            elements[(i * stacks + j) * 6 + 3] = (i * stacks + j) * 4;
            elements[(i * stacks + j) * 6 + 4] = (i * stacks + j) * 4 + 2;
            elements[(i * stacks + j) * 6 + 5] = (i * stacks + j) * 4 + 3;
	}
    }

    auto vert_vbo = std::make_shared<VBO>(vertices, 3);
    auto color_vbo = std::make_shared<VBO>(color, 3);
    auto ebo = std::make_shared<EBO>(elements);

    std::vector<std::shared_ptr<VBO>> vbos = {vert_vbo, color_vbo};

    return std::make_shared<VAO_E>(vbos, ebo, ebo->getLength());
}
*/