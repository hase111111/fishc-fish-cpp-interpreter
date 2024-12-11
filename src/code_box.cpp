
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
                code_box_[y][x] = lines[y][x];
            } else {
                code_box_[y][x] = 0;
            }
        }
    }

    // Reserve the code box.
    ReserveCodeBox(max_width_, max_height_);
}

void CodeBox::SetChar(int x, int y, fchar c) {
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
    for (int y = 0; y < max_height_; ++y) {
        for (int x = 0; x < max_width_; ++x) {
            debug.push_back(code_box_[y][x]);
        }
        debug.push_back('\n');
    }

    debug.push_back('\n');

    for (int x = 0; x < code_box_.size(); ++x) {
        for (int y = 0; y < code_box_[x].size(); ++y) {
            const int c = static_cast<int>(code_box_[x][y]);
            const std::string s = std::to_string(c);

            // 0 padding.
            for (int i = 0; i < 3 - s.size(); ++i) {
                debug.push_back('0');
            }

            debug += s;
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
            code_box_[y][x] = 0;
        }
    }

    for (int y = 0; y < max_height_; y++) {
        for (int x = width; x < temp_width; x++) {
            code_box_[y][x] = 0;
        }
    }
}

}  // namespace fihsc
