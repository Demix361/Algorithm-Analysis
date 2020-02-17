#include "levenshtein.h"
#include <ctime>
#include <chrono>
#include <fstream>
#include <cstring>


#define COUNT_CICLE_1 100
#define COUNT_CICLE_2 1

std::vector<std::vector<std::string>> strings = {{"a", "b"},
                                                {"ab", "ba"},
                                                {"abc", "cba"},
                                                {"abcd", "dcba"},
                                                {"abcde", "edcba"},
                                                {"abcdef", "fedcba"},
                                                {"abcdefg", "gfedcba"},
                                                {"abcdefgh", "jihgfedcba"},
                                                {"abcdefghi", "jihgfedcba"},
                                                {"abcdefghij", "jihgfedcba"}};

std::string mas = "abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghij";
//std::string mas = "abcdefghij";
std::string test_str = "";


void write_to_file(std::ofstream &file, double result) {
    char string[16];
    sprintf(string,"%f",result);
    char *symb = strchr(string, '.');
    *symb = ',';
    file << string << "/";

}

void metering() {
    std::ofstream file;
    file.open("result.txt", std::ios::out);
    unsigned long long int start_time, end_time;
    int res_lev_matr = 0, res_dam_lev_matr = 0, res_dam_lev_rec = 0;
    double result = 0;
    for(int i = 10; i <= 1000; i+=10) {
        test_str += mas;

        file << i << "/";
        result = 0;
        for (int j = 0; j < COUNT_CICLE_1; j++) {
            start_time =  clock();
            res_lev_matr = lev_matr_dist(test_str, test_str);
            end_time =  clock();
            result += double(end_time - start_time);
        }
        result /= COUNT_CICLE_1;
        result /= CLOCKS_PER_SEC;
        write_to_file(file, result);

        result = 0;
        for (int j = 0; j < COUNT_CICLE_1; j++) {
            start_time =  clock();
            res_lev_matr = dam_lev_matr_dist(test_str, test_str);
            end_time =  clock();
            result += double(end_time - start_time);
        }
        result /= COUNT_CICLE_1;
        result /= CLOCKS_PER_SEC;
        write_to_file(file, result);
        file << std::endl;

    }
    file.close();
    std::cout << "OK";


    std::ofstream file_2;
    file_2.open("result_2.txt", std::ios::out);

    for(int i = 1; i <= 10; i+=1) {

        file_2 << i << "/";
        result = 0;
        for (int j = 0; j < COUNT_CICLE_2; j++) {
            start_time =  clock();
            res_lev_matr = lev_matr_dist(strings[i - 1][0], strings[i - 1][1]);
            end_time =  clock();
            result += double(end_time - start_time);
        }
        result /= COUNT_CICLE_2;
        result /= CLOCKS_PER_SEC;
        write_to_file(file_2, result);

        result = 0;
        for (int j = 0; j < COUNT_CICLE_2; j++) {
            start_time =  clock();
            res_lev_matr = dam_lev_rec_dist(strings[i - 1][0], strings[i - 1][1]);
            end_time =  clock();
            result += double(end_time - start_time);
        }
        result /= COUNT_CICLE_2;
        result /= CLOCKS_PER_SEC;
        write_to_file(file_2, result);
        file_2 << std::endl;

    }
    file_2.close();
    std::cout << "OK";
}
