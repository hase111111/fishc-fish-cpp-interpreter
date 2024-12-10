
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // Print usage
        std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
    } else {
        // Read input file
        std::string input_file = argv[1];
        std::cout << "Reading input file: " << input_file << std::endl;
    }

    return 0;
}
