#pragma once

#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/gl_objects/uniform/IUniform.h"

template <typename T>
class Uniform : public IUniform {
public:
    Uniform() {

    }

    Uniform(int loc) : loc(loc) {

    }

    Uniform(const std::string &path) : path(path) {

    }

    Uniform(const T &value) : value(value) {

    }

    virtual ~Uniform() = default;

    virtual void setPath(const std::string &path) {
	this->path = path;
    }

    virtual std::string getPath() const {
	return path;
    }

    virtual void setPrefix(const std::string &prefix) {
	this->prefix = prefix;
    }

    virtual std::string getPrefix() const {
	return prefix;
    }

    virtual void setSuffix(const std::string &suffix) {
	this->suffix = suffix;
    }

    virtual std::string getSuffix() const {
	return suffix;
    }

    virtual std::string getFullPath() const {
	std::string full_path;

	if (!prefix.empty()) {
	    full_path += prefix + ".";
	}

	full_path += path;

	if (!suffix.empty()) {
	    full_path += suffix;
	}

	return full_path;
    }

    void setLoc(int loc) {
	this->loc = loc;
    }

    int getLoc() {
	return loc;
    }

    virtual void updateLoc(GLint program) override {
	this->loc = glGetUniformLocation(program, getFullPath().c_str());
    }

    virtual void setValue(const T& value) {
	this->value = value;
    }

    virtual T getValue() const {
	return value;
    }

    virtual void uniform() const override {
	//empty function
    }
protected:
    std::string path, prefix, suffix;
    GLint loc;
    T value;
};