#include "RootFolder.h"

void fls::RootFolder::add(std::shared_ptr<fls::IFile> file) {
    if (file->getType() == fls::Type::Controller) {
	std::shared_ptr<IRootable> controller = fls::cast<fls::IFile, IRootable>(file);

	if (controller) {
	    std::shared_ptr<fls::File> this_folder = shared_from_this();

	    controller->setRoot(fls::cast<fls::File, fls::IFolder>(this_folder));
	}
    }

    fls::Folder::add(file);
}