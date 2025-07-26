#pragma once

#include <memory>
#include <string>
#include <stdexcept>
#include <stack>
#include <vector>
#include <utility>
#include <iostream>

#include "utils/file/type/Type.h"
#include "utils/file/files/folders/Folder.h"
#include "utils/file/utils/FileUtils.h"
#include "utils/file/utils/FileListener.h"

#include "engine/controller/IRootable.h"
#include "engine/controller/IController.h"

class Engine : public fls::FileListener, public IRootable {
public:
    Engine(const std::string &name);

    Engine(const std::shared_ptr<fls::IFolder> root);

    virtual ~Engine() = default;

    void reg(IRootable &controller);

    void run();

    virtual void setRoot(std::shared_ptr<fls::IFolder> root) override;

    virtual std::shared_ptr<fls::IFolder> getRoot() const override;
private:
    std::shared_ptr<fls::IFolder> root;

    void onFile(std::shared_ptr<fls::IFile> file, std::stack<std::pair<std::shared_ptr<fls::IFolder>, int>> stack) override;
};