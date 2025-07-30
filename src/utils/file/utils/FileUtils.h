#pragma once

#include <vector>
#include <memory>
#include <string>
#include <iostream>

#include "FileListener.h"

#include "utils/file/IFile.h"
#include "utils/file/files/IFolder.h"
#include "utils/file/files/File.h"

namespace fls {

template<typename T, typename V>
std::shared_ptr<V> cast(std::shared_ptr<T> o) {
    return std::dynamic_pointer_cast<V>(o);
}

std::shared_ptr<fls::IFolder> cast_folder(std::shared_ptr<fls::IFile> file);

std::shared_ptr<std::vector<std::string>> separate_path(const std::string &path);

//путь root/game/folder/file1 рабиваетсья на набор запросов, и все под пути (root, game и folder) - это папки.
std::shared_ptr<fls::IFile> get(const std::string &path, std::shared_ptr<fls::IFile> &file);

template<typename T>
std::shared_ptr<T> getAs(const std::string &path, std::shared_ptr<fls::IFile> &file) {
    return std::dynamic_pointer_cast<T>(fls::get(path, file));
}

void run(std::shared_ptr<fls::IFolder> root, fls::FileListener &listener);

}