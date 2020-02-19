#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "const.h"
#include "kmp_search.h"
#include "bm_search.h"
#include "print.h"

void controller() {
    std::string text;
    std::string pattern;


    std::cout << "   Input text : ";
    std::getline(std::cin, text);

    std::cout << "Input pattern : ";
    std::getline(std::cin, pattern);

    std::cout << std::endl;

    std::cout << "   Text = \"" << text << "\"" << std::endl;
    std::cout << "Pattern = \"" << pattern << "\"" << std::endl;

    std::cout << std::endl;

    int kmp_ind = kmp_search(text, pattern);
    int bm_ind = bm_search(text, pattern);

    std::cout << "KMP = " <<
    (WRONG_LEN == kmp_ind ? "wrong length!" :
    (NOT_FOUND == kmp_ind ? "not found!" :
    std::to_string(kmp_ind))) << std::endl;

    std::cout << " BM = " <<
    (WRONG_LEN == bm_ind ? "wrong length!" :
    (NOT_FOUND == bm_ind ? "not found!" :
    std::to_string(bm_ind))) << std::endl;

    std::cout << std::endl;
}
