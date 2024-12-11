
#ifndef FIHSC_CODE_BOX_H_
#define FIHSC_CODE_BOX_H_

#include <string>
#include <vector>

namespace fishc {

using fchar = char;  //!< Fishc char type.

class CodeBox final {
  public:
    CodeBox() = delete;
    CodeBox(const std::string& code);
    ~CodeBox() = default;

    inline int GetMaxWidth() const { return max_width_; }
    inline int GetMaxHeight() const { return max_height_; }

    inline fchar GetChar(int x, int y) const { 
        if (x < 0 || x >= max_width_ || y < 0 || y >= max_height_) {
            return 0;
        }
        return code_box_[y][x]; 
    }
    void SetChar(int x, int y, fchar c);

    std::string DebugString() const;

  private:
    void ReserveCodeBox(int width, int height);

    std::vector<std::vector<fchar>> code_box_;

    int max_width_{0};
    int max_height_{0};
};

}  // namespace fihsc

#endif  // FIHSC_CODE_BOX_H_
