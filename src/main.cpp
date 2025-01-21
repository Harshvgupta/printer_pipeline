#include "fakeprinter/fake_printer.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <print_name> <output_dir> <mode>\n";
        std::cout << "mode: supervised or automatic\n";
        return 1;
    }

    std::string printName = argv[1];
    std::string outputDir = argv[2];
    std::string mode = argv[3];
    bool supervisedMode = (mode == "supervised");

    printer::FakePrinter printer(printName, outputDir, supervisedMode);
    printer.run();

    return 0;
}