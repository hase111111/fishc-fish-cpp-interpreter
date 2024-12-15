
#include "argument_help_printer.h"

#include <iostream>

#include "version.h"

namespace fishc {

ArgumentHelpPrinter::ArgumentHelpPrinter(
    const std::vector<Argument> &argument_settings) noexcept
    : argument_settings_{argument_settings} 
    , required_argument_idx_{GetRequiredArgumentIdx()} {}

void ArgumentHelpPrinter::Print() const noexcept {
    PrintUsage();
    std::cout << std::endl;

    PrintRequiredArguments();
    std::cout << std::endl;

    PrintOptionalArguments();
    std::cout << std::endl;
}

std::set<int> ArgumentHelpPrinter::GetRequiredArgumentIdx() const noexcept {
    std::set<int> required_argument_idx;
    for (int i = 0; i < static_cast<int>(argument_settings_.size()); ++i) {
        if (argument_settings_[i].is_required) {
            required_argument_idx.insert(i);
        }
    }

    return required_argument_idx;
}

void ArgumentHelpPrinter::PrintUsage() const noexcept {
    std::cout << "Usage: " << kProgramName << " [-h] ";

    if (!required_argument_idx_.empty()) {
        std::cout << "(";
        for (const auto &idx : required_argument_idx_) {
            if (argument_settings_[idx].is_option) {
                std::cout << argument_settings_[idx].names[0];
                if (argument_settings_[idx].need_argument) {
                    std::cout << " <" << argument_settings_[idx].argument_name << ">";
                }
            } else {
                std::cout << "<" << argument_settings_[idx].names[0] << ">";
            }

            if (idx != *required_argument_idx_.rbegin()) {
                std::cout << " | ";
            }
        }
        std::cout << ")";
    }

    if (required_argument_idx_.size() < argument_settings_.size()) {
        std::cout << " [options]";
    }

    std::cout << std::endl;
}

void ArgumentHelpPrinter::PrintRequiredArguments() const noexcept {
    std::cout << "required arguments:" << std::endl;
    for (const auto &idx : required_argument_idx_) {
        std::cout << "  ";
        for (const auto &name : argument_settings_[idx].names) {
            std::cout << name << " ";
            if (argument_settings_[idx].need_argument && argument_settings_[idx].is_option) {
                std::cout << "<" << argument_settings_[idx].argument_name << "> ";
            }
        }
        std::cout << std::endl;
        std::cout << "    " << argument_settings_[idx].description << std::endl;
    }
}

void ArgumentHelpPrinter::PrintOptionalArguments() const noexcept {
    std::cout << "optional arguments:" << std::endl;
    for (int i = 0; i < static_cast<int>(argument_settings_.size()); ++i) {
        if (required_argument_idx_.find(i) != required_argument_idx_.end()) {
            continue;
        }

        std::cout << "  ";
        for (const auto &name : argument_settings_[i].names) {
            std::cout << name << " ";
            if (argument_settings_[i].need_argument) {
                std::cout << "<" << argument_settings_[i].argument_name << "> ";
            }
        }
        std::cout << std::endl;
        std::cout << "    " << argument_settings_[i].description << std::endl;
    }
}

}  // namespace fishc
