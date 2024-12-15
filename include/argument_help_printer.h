
#ifndef FISHC_ARGUMENT_HELP_PRINTER_H_
#define FISHC_ARGUMENT_HELP_PRINTER_H_

#include <set>
#include <vector>

#include "argument.h"

namespace fishc {

class ArgumentHelpPrinter final {
 public:
    ArgumentHelpPrinter() = delete;
    ArgumentHelpPrinter(
      const std::vector<Argument> &argument_settings) noexcept;
    ~ArgumentHelpPrinter() = default;

    void Print() const noexcept;

  private:
    [[nodiscard]]
    std::set<int> GetRequiredArgumentIdx() const noexcept;

    void PrintUsage() const noexcept;
    void PrintRequiredArguments() const noexcept;
    void PrintOptionalArguments() const noexcept;

    const std::vector<Argument> &argument_settings_;
    std::set<int> required_argument_idx_;
};

}  // namespace fishc

#endif  // FISHC_ARGUMENT_HELP_PRINTER_H_
