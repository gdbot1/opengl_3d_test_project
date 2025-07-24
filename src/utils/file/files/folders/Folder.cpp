#include "Folder.h"

fls::Folder::Folder(const std::string &name) : File(name, fls::Type::Folder) {}

fls::Folder::~Folder() {}

void fls::Folder::add(std::shared_ptr<fls::IFile> file) {
    auto it = file_table.find(file->getName());

    if (it == file_table.end()) {
	//add to folder
	file_table[file->getName()] = file;
	files.push_back(file);

	//change parent file
	file->setParent(shared_from_this());
    }

    //error (file are already added to list)
}

void fls::Folder::remove(const std::string &name) {
    file_table.erase(name);

    for (int i = 0; i < files.size(); i++) {
	std::shared_ptr<IFile> file = files[i];
	if (file->getName() == name) {
	    files.erase(files.begin() + i);
	    file->setParent(nullptr);//удаление parent. Тут узкое место, так-как setParent правоцирует двойное удаление
	    break;
	}
    }
}

std::shared_ptr<fls::IFile> fls::Folder::get(const std::string &name) const {
    auto it = file_table.find(name);

    if (it == file_table.end()) {
	return nullptr;
	//throw std::runtime_error("FOLDER ERROR: get(name) error: file \"" + name + "\" not founded");
    }
    else {
	return it->second;
    }
}

bool fls::Folder::contains(const std::string &name) const {
    return file_table.find(name) != file_table.end();
}

std::vector<std::shared_ptr<fls::IFile>> fls::Folder::getFiles() const {
    return this->files;
}