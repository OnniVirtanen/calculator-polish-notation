#include <iostream>
#include "calculator.h"

int main() {

    Calculator calculator;
    std::string input;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break; // Exit loop and program
        }

        if (input.find('=') != std::string::npos) {
            try {
                double result = calculator.calculate(input);
                std::cout << "Result: " << result << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error calculating expression: " << e.what() << std::endl;
            }
        } else {
            std::cerr << "Invalid input. Remember to end expressions with '=' to calculate." << std::endl;
        }
    }

    return 0;
}
