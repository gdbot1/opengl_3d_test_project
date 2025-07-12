#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>

template <typename T>
class GenericFolder {
public:
    GenericFolder() = default;
    
    virtual ~GenericFolder() = default;

    void add(const std::string &name, const T &t) {
	if (!contains(name)) {
	    table[name] = t;
	    elements.push_back(t);
	}
	else {
	    throw std::runtime_error("FOLDER ERROR: add(string, t) error: element \"" + name + "\" is already added to folder");
	}
    }

    void remove(const std::string &name) {
	auto it = table.find(name);

	if (it != table.end()) {
	    const T &t = it->second;

	    table.erase(name);

	    for (size_t i = 0; i < elements.size(); i++) {
		if (t != elements[i]) {
		    continue;
		}

		elements.erase(elements.begin() + i);

		break;
	    }
	}
    }

    bool contains(const std::string &name) const {
	auto it = table.find(name);

	return it != table.end();
    }

    T& get(const std::string &name) {
	auto it = table.find(name);

	if (it == table.end()) {
	    throw std::runtime_error("FOLDER ERROR: get(name) error: element with name: \"" + name + "\" not found");
	}

	return it->second;
    }

    std::vector<T>& getElements() {
	return elements;
    }
private:
    std::unordered_map<std::string, T> table;
    std::vector<T> elements;
};