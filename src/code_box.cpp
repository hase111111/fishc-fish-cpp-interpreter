
#include "code_box.h"

#include <stdexcept>

namespace fishc {

CodeBox::CodeBox(const std::string& code) {
    // Split the code into lines.
    std::vector<std::string> lines;
    std::string line;
    for (const auto& c : code) {
        if (c == '\n') {
            lines.push_back(line);
            line.clear();
        } else {
            line.push_back(c);
        }
    }
    lines.push_back(line);

    // Find the max width and height.
    for (const auto& l : lines) {
        if (l.size() > max_width_) {
            max_width_ = l.size();
        }
    }
    max_height_ = lines.size();

    // Create the code box.
    code_box_.resize(max_height_);
    for (auto& c : code_box_) {
        c.resize(max_width_);
    }

    // Fill the code box.
    for (int y = 0; y < max_height_; y++) {
        for (int x = 0; x < max_width_; x++) {
            if (x < lines[y].size()) {
                Number n = static_cast<ImplInt>(lines[y][x]);
                code_box_[y][x] = n;
            } else {
                code_box_[y][x] = static_cast<ImplInt>(0);
            }
        }
    }

    // Reserve the code box.
    ReserveCodeBox(max_width_, max_height_);
}

void CodeBox::SetChar(int x, int y, Number c) {
    if (x < 0 || y < 0) {
        throw std::runtime_error("CodeBox::SetChar: x or y is less than 0.");
    }

    if (x >= max_width_) {
        ReserveCodeBox(x, max_height_);

        // Update the max width.
        max_width_ = x + 1;
    }

    if (y >= max_height_) {
        ReserveCodeBox(max_width_, y);

        // Update the max height.
        max_height_ = y + 1;
    }
    
    code_box_[y][x] = c;
}

std::string CodeBox::DebugString() const {
    std::string debug;
    debug += "max_width: " + std::to_string(max_width_) + '\n';
    debug += "max_height: " + std::to_string(max_height_) + '\n';
    debug += "code_box:\n";
    for (int y = 0; y < max_height_; ++y) {
        for (int x = 0; x < max_width_; ++x) {
            if (code_box_[y][x].index() == 0) {
                ImplInt i = std::get<ImplInt>(code_box_[y][x]);
                debug.push_back(static_cast<char>(i));
            } else {
                debug.push_back(' ');
            }
        }
        debug.push_back('\n');
    }

    debug.push_back('\n');
    debug += "code_box (number):\n";

    for (int x = 0; x < code_box_.size(); ++x) {
        for (int y = 0; y < code_box_[x].size(); ++y) {
            if (code_box_[x][y].index() == 0) {
                ImplInt i = std::get<ImplInt>(code_box_[x][y]);
                debug += std::to_string(i);
            } else {
                ImplFloat f = std::get<ImplFloat>(code_box_[x][y]);
                debug += std::to_string(f);
            }
            debug.push_back(' ');
        }
        debug.push_back('\n');
    }
    return debug;
}

void CodeBox::ReserveCodeBox(int width, int height) {
    // Double the size of the code box.
    const int temp_width = width * 2;
    const int temp_height = height * 2;

    code_box_.resize(temp_height);
    for (auto& c : code_box_) {
        c.resize(temp_width);
    }

    // Fill the code box.
    for (int y = height; y < temp_height; y++) {
        for (int x = 0; x < temp_width; x++) {
            code_box_[y][x] = static_cast<ImplInt>(0);
        }
    }

    for (int y = 0; y < max_height_; y++) {
        for (int x = width; x < temp_width; x++) {
            code_box_[y][x] = static_cast<ImplInt>(0);
        }
    }
}

}  // namespace fihsc
