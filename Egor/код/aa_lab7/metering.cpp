#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <functional>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include "kmp_search.h"
#include "bm_search.h"
#include "print.h"
#include "const.h"

const int ascii_len = 123 - 97;
std::vector<char> ascii_table(ascii_len);

std::string get_rand_str(int len) {
    std::string pattern(len, 'a');
    for (int i = 0; i < len; ++i) {
        pattern[i] = ascii_table[rand() % ascii_len];
    }

    return pattern;
}

std::string get_rand_str_(int len) {
    std::string pattern(len, 'a');
    for (int i = 0; i < len; ++i) {
        pattern[i] = (i % 2 ? 'a' : 'b');
    }

    return pattern;
}

#define NUM 1
#define START 0
#define STEP  100000
#define STOP  1000000

void test_time(std::string file_name) {
    srand(static_cast<unsigned int>(time(0)));
    std::cout << std::endl << "--[ " << file_name << " ]--" << std::endl;

    std::ofstream fout(file_name);
    std::chrono::time_point<std::chrono::system_clock> kmp_start, kmp_end;
    std::chrono::time_point<std::chrono::system_clock> bm_start, bm_end;

    // const int text_len = 600;
    const int pattern_len = 100;

    for (int i = START; i <= STOP; i += STEP) {
        std::cout << "Cur_size = " << i << std::endl;
        fout << "SIZE { " << i << " } :" << std::endl;

        unsigned long long int kmp_elapsed = 0;
        unsigned long long int bm_elapsed = 0;

        int kmp_res = 0, bm_res = 0;

        for (int j = 0; j < NUM; ++j) {
            // auto text = get_rand_str(i);
            // auto pattern = get_rand_str(pattern_len);
            auto text = std::string(i, 'a');
            auto pattern = get_rand_str_(pattern_len);
            //std::cout << text << std::endl;
            //std::cout << pattern << std::endl;

            kmp_start = std::chrono::system_clock::now();
            kmp_res = kmp_search(text, pattern);
            kmp_end = std::chrono::system_clock::now();

            kmp_elapsed += std::chrono::duration_cast<std::chrono::microseconds>
            (kmp_end - kmp_start).count();


            bm_start = std::chrono::system_clock::now();
            bm_res = bm_search(text, pattern);
            bm_end = std::chrono::system_clock::now();

            bm_elapsed += std::chrono::duration_cast<std::chrono::microseconds>
            (bm_end - bm_start).count();

            assert(kmp_res == bm_res);
        }

        fout << kmp_elapsed << " " << bm_elapsed << std::endl;

        // fout << ((long double)(kmp_elapsed) / NUM) << " " <<
        // ((long double)(bm_elapsed) / NUM) << std::endl;

        std::cout << "Continue..." << std::endl;
    }

    fout.close();
}

int main() {
    for (char ch = 97; ch < 123; ++ch) {
        ascii_table[ch - 97] = ch;
    }

    std::cout << std::endl << "Start..." << std::endl;

    test_time("t3.txt");  

    std::cout << std::endl << "All tests were run!" << std::endl;

    return 0;
}
