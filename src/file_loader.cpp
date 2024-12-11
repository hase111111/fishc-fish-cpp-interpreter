
#include <fstream>

#include "file_loader.h"


namespace fishc {

FileLoader::FileLoader(const std::string& file_path) {
    std::ifstream file(file_path);

    if (!file.is_open()) {
        is_open_ = false;
        return;
    }

    is_open_ = true;

    std::string line;
    while (std::getline(file, line)) {
        file_ += line + '\n';
    }

    file.close();

    if (file_.empty()) {
        is_open_ = false;
    }

    return;
}

}  // namespace fishc
