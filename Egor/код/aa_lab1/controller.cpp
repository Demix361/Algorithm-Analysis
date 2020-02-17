#include "controller.h"
#include "levenshtein.h"

void enter_word(std::string &str, std::string message) {
    std::cout << message;
    std::getline(std::cin, str);
}

void controller() {
    std::string source_word, check_word;
    //std::shared_ptr<std::string> ptr_word(source_word);

    enter_word(source_word, "Enter source word: ");
    enter_word(check_word, "Enter check word: ");

    std::cout << source_word.size() << std::endl;

    int result = 0;
    result = lev_matr_dist(source_word, check_word);
    std::cout << "Levenshtein matrix result: " << result << std::endl;

    result = dam_lev_matr_dist(source_word, check_word);
    std::cout << "Damerau - Levenshtein matrix result: " << result << std::endl;

    result = dam_lev_rec_dist(source_word, check_word);
    std::cout << "Damerau - Levenshtein recursion result: " << result << std::endl;
}
