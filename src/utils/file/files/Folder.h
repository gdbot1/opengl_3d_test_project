#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include <stdexcept>

#include "utils/file/File.h"

//fls - FiLe System

namespace fls {

class Folder : public File {
public:
    Folder(const std::string &name);

    virtual ~Folder();

    virtual void add(std::shared_ptr<fls::File> file);

    virtual void remove(const std::string &name);

    virtual std::shared_ptr<fls::File> get(const std::string &name) const;

    template<typename T>
    std::shared_ptr<T> getAs(const std::string &name) const {
	//auto obj = std::dynamic_pointer_cast<T>(this->get(name));
	
	return std::dynamic_pointer_cast<T>(this->get(name));

	/*
	if (obj != nullptr) {
	    return obj;
	}
	else {
	    return nullptr;
	    //throw std::runtime_error("FOLDER ERROR: get(name) error: tried to take other types of objects");
	}
	*/
    }

    virtual bool contains(const std::string &name) const;

    virtual std::vector<std::shared_ptr<fls::File>> getFiles() const;
protected:
    std::unordered_map<std::string, std::shared_ptr<fls::File>> file_table;
    std::vector<std::shared_ptr<fls::File>> files;
};

}