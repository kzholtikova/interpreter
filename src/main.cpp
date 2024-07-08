#include <iostream>
#include <string>
#include "../include/interpreter.h"

int main() {
    std::string line;
    std::getline(std::cin, line);
    while (!line.empty()) {
        try {
            Interpreter::processLine(line);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << "\n";
            std::exit(EXIT_FAILURE);
        }

        std::getline(std::cin, line);
    }

    return 0;
}
