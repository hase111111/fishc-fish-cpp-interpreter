
#ifndef FISHC_FILE_LOADER_H_
#define FISHC_FILE_LOADER_H_

#include <string>

namespace fishc {

class FileLoader final {
  public:
    FileLoader() = delete;
    FileLoader(const std::string& file_path);

    inline bool IsOpen() const { return is_open_; }
    std::string GetFile() const { return file_; }

  private:
    std::string file_;
    bool is_open_;
};

}  // namespace fishc

#endif  // FISHC_FILE_LOADER_H_
