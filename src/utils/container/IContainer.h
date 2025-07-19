#pragma once

#include <unordered_map>
#include <memory>
#include <vector>

template<typename T>
class IContainer {
public:
    virtual void add(std::shared_ptr<T> t) = 0;

    virtual void remove(const std::string &name) = 0;

    virtual std::shared_ptr<T> get(const std::string &name) const = 0;

    virtual bool contains(const std::string &name) const = 0;

    virtual std::vector<std::shared_ptr<T>> getFiles() const = 0;
};