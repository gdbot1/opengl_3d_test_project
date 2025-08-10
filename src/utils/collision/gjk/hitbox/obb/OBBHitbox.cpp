#include "OBBHitbox.h"

gjk::OBBHitbox::OBBHitbox(const std::vector<glm::vec3> vertices, std::shared_ptr<mtrx::TransformMatrix> model_matrix) : vertices(vertices), model_matrix(model_matrix) {}

glm::vec3 gjk::OBBHitbox::support(glm::vec3 direction) const {
    glm::mat4 mat = model_matrix->getMatrix();

    glm::vec3 correct_direction = glm::vec3(glm::inverse(mat) * glm::vec4(direction, 0.0f)); 

    float max_scal = -std::numeric_limits<float>::max();
    glm::vec3 sup = vertices[0], direction_n = glm::normalize(direction);

    for (int i = 0; i < vertices.size(); i++) {
	glm::vec3 vertex = vertices[i];

	float scalar = glm::dot(vertex, direction_n);

	if (scalar > max_scal) {
	    max_scal = scalar;
	    sup = vertex;
	}
    }

    glm::vec3 e_sup = glm::vec3(mat * glm::vec4(sup, 1.0f));

    return e_sup;
}

glm::vec3 gjk::OBBHitbox::getCenter() const {
    return glm::vec3(model_matrix->getMatrix() * glm::vec4(0, 0, 0, 1.0f));
}