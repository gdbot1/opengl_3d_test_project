#pragma once

#include <unordered_map>
#include <any>
#include <string>

class Storage {
public:
    Storage() = default;

    ~Storage() = default;

    template<typename T>
    void set(const std::string &key, T &value) {
	storage[key] = value;
    }

    template<typename T>
    T get(const std::string &key) {
	auto it = storage.find(key);

	if (it == storage.end()) {
	    throw runtime_error("STORAGE ERROR: get() error: key not found for key: " + key);
	}
	else {
	    try {
	        return std::any_cast<T>(it->second);
	    }
	    catch (const bad_any_cast& e) {
		throw runtime_error("STORAGE ERROR: get() error: bad any_cast for key: " + key);
	    }
	}
    }

    void remove(const std::string &key) {
	storage.erase(key);
    }

    bool contains(const std::string &key) {
	return storage.find(key) != storage.end();
    }
private:
    std::unordered_map<std::string, std::any> storage;
};