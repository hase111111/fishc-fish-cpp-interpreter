
#include "argument_parser.h"
#include "file_loader.h"

namespace fishc {

ArgumentParser::ArgumentParser(int argc, char *argv[]) {
    if (argc < 2) {
        // first argument is the program name, so we need at least 2 arguments.
        // activate the help mode.
        option_.is_help_mode = true;
        return;
    }

    // check if the first argument is a code path.
    std::string first_arg = argv[1];

    FileLoader file_loader(first_arg);
    if (file_loader.IsOpen()) {
        option_.code = file_loader.GetFile();
        has_code_ = true;
    }

    // If has not code, actiavte the help mode.
    if (!has_code_) {

        option_.is_help_mode = true;
    }
}

}  // namespace fishc