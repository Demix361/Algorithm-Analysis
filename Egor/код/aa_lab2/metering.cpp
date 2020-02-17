
#include <ctime>
#include <chrono>
#include <fstream>
#include <cstring>


#include "mult_matrix.h"



#define COUNT_CICLE 10


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


void gener_matrix(Matrix &matr) {
    size_t n = matr.size();
    size_t m = matr[0].size();
    for (size_t i = 0; i < n; i++) {
        for(size_t j = 0; j < m; j++) {
            matr[i][j] = rand();
        }
    }
}

void write_to_file(std::ofstream &file, double result) {
    char string[16];
    sprintf(string,"%f",result);
    char *symb = strchr(string, '.');
    *symb = ',';
    file << string << "/";

}

void metering() {
    unsigned long long int start_time, end_time;
    double result = 0;



    std::cout << CLOCKS_PER_SEC << std::endl;
    std::ofstream file;
    file.open("result.txt", std::ios::out);


    for(int i = 100; i <= 1000; i+=100) {
        cout << i << endl;
        test_str += mas;
        Matrix matr_1(i, Vector(i, 0));
        Matrix matr_2(i, Vector(i, 0));

        gener_matrix(matr_1);
        gener_matrix(matr_2);
        file << i << "/";
        result = 0;
        for (int j = 0; j < COUNT_CICLE; j++) {
            Matrix matr_res(i, Vector(i, 0));
            start_time =  clock();
            mult_matrix_std(matr_1, matr_2, matr_res);
            end_time =  clock();
            result += double(end_time - start_time);
        }
        result /= COUNT_CICLE;
        result /= CLOCKS_PER_SEC;
        write_to_file(file, result);

        result = 0;
        for (int j = 0; j < COUNT_CICLE; j++) {
            Matrix matr_res(i, Vector(i, 0));
            start_time =  clock();
            mult_matrix_vinograd(matr_1, matr_2, matr_res);
            end_time =  clock();
            result += double(end_time - start_time);
        }
        result /= COUNT_CICLE;
        result /= CLOCKS_PER_SEC;
        write_to_file(file, result);

        result = 0;
        for (int j = 0; j < COUNT_CICLE; j++) {
            Matrix matr_res(i, Vector(i, 0));
            start_time =  clock();
            mult_matrix_vinograd_optimiz(matr_1, matr_2, matr_res);
            end_time =  clock();
            result += double(end_time - start_time);
        }
        result /= COUNT_CICLE;
        result /= CLOCKS_PER_SEC;
        write_to_file(file, result);
        file << std::endl;

    }

    for(int i = 101; i <= 1001; i+=100) {
        cout << i << endl;
        test_str += mas;
        Matrix matr_1(i, Vector(i, 0));
        Matrix matr_2(i, Vector(i, 0));

        gener_matrix(matr_1);
        gener_matrix(matr_2);
        file << i << "/";
        result = 0;
        for (int j = 0; j < COUNT_CICLE; j++) {
            Matrix matr_res(i, Vector(i, 0));
            start_time =  clock();
            mult_matrix_std(matr_1, matr_2, matr_res);
            end_time =  clock();
            result += double(end_time - start_time);
        }
        result /= COUNT_CICLE;
        write_to_file(file, result);

        result = 0;
        for (int j = 0; j < COUNT_CICLE; j++) {
            Matrix matr_res(i, Vector(i, 0));
            start_time =  clock();
            mult_matrix_vinograd(matr_1, matr_2, matr_res);
            end_time =  clock();
            result += double(end_time - start_time);
        }
        result /= COUNT_CICLE;
        write_to_file(file, result);

        result = 0;
        for (int j = 0; j < COUNT_CICLE; j++) {
            Matrix matr_res(i, Vector(i, 0));
            start_time =  clock();
            mult_matrix_vinograd_optimiz(matr_1, matr_2, matr_res);
            end_time =  clock();
            result += double(end_time - start_time);
        }
        result /= COUNT_CICLE;
        write_to_file(file, result);
        file << std::endl;

    }
    file.close();
    std::cout << "OK";


}
