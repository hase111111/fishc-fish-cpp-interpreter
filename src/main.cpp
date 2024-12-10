
#include <iostream>

#include "help_printer.h"
#include "option_loader.h"

int main(int argc, char *argv[]) {
    using fishc::HelpPrinter;
    using fishc::OptionLoader;

    OptionLoader option_loader;
    option_loader.Load(argc, argv);

    if (option_loader.GetOptionNum() == 0) {
        HelpPrinter::PrintHelp();
    }

    return 0;
}
