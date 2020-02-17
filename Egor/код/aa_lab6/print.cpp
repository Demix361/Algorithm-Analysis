#include "print.h"

void board() {
    for (size_t i = 0; i < BOARD_LENGTH; i++) {
        std::cout << "=";
    }

    std::cout << std::endl;
}

void print_way(std::vector<int> way) {
    std::cout << "Way : ( " << way[0] + 1;
    for (int i = 1; i < static_cast<int>(way.size()); ++i) {
        std::cout << " -> " << way[i] + 1;
    }

    std::cout << " ) " << std::endl;
}

// void print_way(std::vector<int> way) {
//     std::cout << "Way : $( " << way[0] + 1;
//     for (int i = 1; i < static_cast<int>(way.size()); ++i) {
//         std::cout << " \\rightarrow " << way[i] + 1;
//     }

//     std::cout << " )$ " << std::endl;
// }
