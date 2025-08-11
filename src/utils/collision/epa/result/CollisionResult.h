#pragma once

#include <glm/glm.hpp>

namespace epa {

struct CollisionResult {
    bool status;
    glm::vec3 vector;
    float depth;

    CollisionResult(bool status, const glm::vec3 &vector, float depth) : status(status), vector(vector), depth(depth) {}

    CollisionResult() : status(false), vector(glm::vec3(0, 0, 0)), depth(0.0f) {}

    virtual ~CollisionResult() = default;

    CollisionResult& setStatus(bool status) {
	this->status = status;

	return *this;
    }

    CollisionResult& setVector(const glm::vec3 &vector) {
	this->vector = vector;

	return *this;
    }

    CollisionResult& setDepth(float depth) {
	this->depth = depth;

	return *this;
    }
};

}