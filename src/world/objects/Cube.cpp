#include "Cube.h"

Cube::Cube(float x, float y, float z, float width, float height, float depth) : Object(createCube(x, y, z, width, height, depth)) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->width = width;
    this->height = height;
    this->depth = depth;
}

Cube::~Cube() {

}

glm::vec3 Cube::getPosition() {
    return glm::vec3(x, y, z);
}

glm::vec3 Cube::getSize() {
    return glm::vec3(width, height, depth);
}

shared_ptr<VAO> Cube::createCube(float x, float y, float z, float width, float height, float depth) {
    std::cout << "CREATING CUBE: calc vertices" << std::endl;

    std::vector<float> vertices = {
	//top
	x, y + height, z,
	x + width, y + height, z,
	x + width, y + height, z + depth,
	x, y + height, z + depth,

	//bot
	x, y, z,
	x + width, y, z,
	x + width, y, z + depth,
	x, y, z + depth,

	//right
	x + width, y, z,
	x + width, y + height, z,
	x + width, y + height, z + depth,
	x + width, y, z + depth,

	//left
	x, y, z,
	x, y + height, z,
	x, y + height, z + depth,
	x, y, z + depth,

	//front
	x, y, z + depth,
	x + width, y, z + depth,
	x + width, y + height, z + depth,
	x, y + height, z + depth,

	//back
	x, y, z,
	x + width, y, z,
	x + width, y + height, z,
	x, y + height, z
    };

    std::vector<float> texCords = {
	0, 1,
	1, 1,
	1, 0,
	0, 0,

	0, 1,
	1, 1,
	1, 0,
	0, 0,

	0, 1,
	1, 1,
	1, 0,
	0, 0,

	0, 1,
	1, 1,
	1, 0,
	0, 0,

	0, 1,
	1, 1,
	1, 0,
	0, 0,

	0, 1,
	1, 1,
	1, 0,
	0, 0,
    };

    std::cout << "CREATING CUBE: calc color" << std::endl;

    std::vector<float> colors;

    for (int i = 0; i < 4; i++) {
	colors.push_back(0);//r
	colors.push_back(0);//g
	colors.push_back(1);//b
    }

    for (int i = 4; i < 8; i++) {
	colors.push_back(1);//r
	colors.push_back(1);//g
	colors.push_back(0);//b
    }

    for (int i = 8; i < 12; i++) {
	colors.push_back(1);//r
	colors.push_back(0);//g
	colors.push_back(0);//b
    }

    for (int i = 12; i < 16; i++) {
	colors.push_back(0);//r
	colors.push_back(1);//g
	colors.push_back(1);//b
    }

    for (int i = 16; i < 20; i++) {
	colors.push_back(0);//r
	colors.push_back(1);//g
	colors.push_back(0);//b
    }

    for (int i = 20; i < 24; i++) {
	colors.push_back(1);//r
	colors.push_back(0);//g
	colors.push_back(1);//b
    }
    
    std::vector<int> ind = {
	0, 1, 2,
	0, 2, 3,

	4, 5, 6,
	4, 6, 7,
	
	8, 9, 10,
	8, 10, 11,
	
	12, 13, 14,
	12, 14, 15,

	16, 17, 18,
	16, 18, 19,

	20, 21, 22,
	20, 22, 23
    };

    std::cout << "CREATING CUBE: building cube" << std::endl;

    return make_shared<VAO_E>(std::vector<std::shared_ptr<VBO>>{
	make_shared<VBO>(vertices, 3),
	make_shared<VBO>(colors, 3),
	make_shared<VBO>(texCords, 2)
    }, make_shared<EBO>(ind), static_cast<int>(ind.size()));
}