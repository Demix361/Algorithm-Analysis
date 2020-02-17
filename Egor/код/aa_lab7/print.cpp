#include "print.h"

void board() {
    for (size_t i = 0; i < BOARD_LENGTH; i++) {
        std::cout << "~";
    }
    
    std::cout << std::endl;
}

void print(const std::vector<int> &v) {
    for (auto elem : v) {
        std::cout << elem << " ";
    }

    std::cout << std::endl;
}
