#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include <stdexcept>

#include "utils/file/File.h"
#include "IFolder.h"

//fls - FiLe System

namespace fls {

class Folder : public fls::File, public fls::IFolder {
public:
    Folder(const std::string &name);

    virtual ~Folder();

    virtual void add(std::shared_ptr<fls::IFile> file) override;

    virtual void remove(const std::string &name) override;

    virtual std::shared_ptr<fls::IFile> get(const std::string &name) const override;

    virtual bool contains(const std::string &name) const override;

    virtual std::vector<std::shared_ptr<fls::IFile>> getFiles() const override;
protected:
    std::unordered_map<std::string, std::shared_ptr<fls::IFile>> file_table;
    std::vector<std::shared_ptr<fls::IFile>> files;
};

}