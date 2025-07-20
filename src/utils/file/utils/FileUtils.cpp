#include "FileUtils.h"

std::shared_ptr<fls::IFolder> fls::cast_folder(std::shared_ptr<fls::IFile> file) {
    return cast<fls::IFile, fls::IFolder>(file);
}

std::shared_ptr<std::vector<std::string>> fls::separate_path(const std::string &path) {
    std::shared_ptr<std::vector<std::string>> separated_path = std::make_shared<std::vector<std::string>>();

    std::string s;

    for (int i = 0; i < path.size(); i++) {
	if (path[i] == '/' || path[i] == '\\') {
	    separated_path->push_back(s);
	    s = "";

	    continue;
	}

	s += path[i];
    }

    separated_path->push_back(s);

    return separated_path;
}

std::shared_ptr<fls::IFile> fls::get(const std::string &path, std::shared_ptr<fls::IFile> &file) {
    std::shared_ptr<std::vector<std::string>> s_path = separate_path(path);

    std::shared_ptr<fls::IFile> c_file = file;// current folder / cursor

    for (int i = 0; i < s_path->size() - 1; i++) {
	std::string c_path = (*s_path)[i];//current path

	if (c_path == "..") {
	    c_file = cast_folder(c_file->getParent());
	}
	else {
	    std::shared_ptr<IFolder> c_folder = cast_folder(c_file);

	    if (!c_folder) {
		return nullptr;
	    }

	    c_file = c_folder->getAs<fls::IFile>(c_path);
	}

	if (!c_file) {
	    return nullptr;//попытка обратиться через файл, как через папку (file/file2 - ошибка), или файла не существует
	}
    }

    std::string lp_path = (*s_path)[s_path->size() - 1];//last part of the path

    return lp_path == ".." ? c_file->getParent() : cast_folder(c_file)->get(lp_path);
}