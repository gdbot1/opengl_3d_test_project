#pragma once

#include <vector>
#include <string>
#include <utility>
#include <memory>

#include "graphics/gl_objects/uniform/Uniform.h"
#include "graphics/gl_objects/uniform/utils/UniformUtils.h"

template <typename T>
class ArrayUniform : public Uniform<std::vector<std::shared_ptr<Uniform<T>>>> {
public:
    ArrayUniform(int length, const std::string &path) : Uniform(path), length(length) {
	fill(length);

	setPath(path);
    }

    ArrayUniform(int length) : length(length) {
	fill(length);
    }

    virtual ~ArrayUniform() = default;

    virtual void updateLoc(GLint program) override {
	for (int i = 0; i < length; i++) {
	    value[i]->updateLoc(program);
	}
    }

    virtual void uniform() const override {
	for (int i = 0; i < length; i++) {
	    value[i]->uniform();
	}
    }

    virtual void setPath(const std::string &path) override {
	this->path = path;    

	for (int i = 0; i < length; i++) {
	    update(i);
	}
    }

    virtual void setPrefix(const std::string &prefix) override {
	this->prefix = prefix;    

	for (int i = 0; i < length; i++) {
	    update(i);
	}
    }

    virtual void set(int i, std::shared_ptr<Uniform<T>> val) {
	if (i < 0 || i >= length) {
	    return;//i going out of the array ranges
	}

	uniform::swap<T>(value[i], val);

	value[i] = val;
    }

    virtual void remove(int i) {
	if (i < 0 || i >= length) {
	    return;//i going out of the array ranges
	}
	
	set(i, std::make_shared<Uniform<T>>());
	
	//value.erase(value.begin() + i);//deleting i-element
    }

    virtual std::shared_ptr<Uniform<T>> get(int i) const {
	if (i < 0 || i >= length) {
	    return nullptr;//i going out of the array ranges
	}

	return value[i];
    }

    virtual int getLength() const {
	return length;
    }
private:
    int length;

    void fill(int length) {
	for (int i = 0; i < length; i++) {
	    value.push_back(std::make_shared<Uniform<T>>());
	}
    }

    void update(int i) {
	value[i]->setPrefix(prefix);
	value[i]->setPath(path);
	value[i]->setSuffix("[" + std::to_string(i) + "]");
    }
};