
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
    double result = 0;


    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::ofstream file;
    file.open("result_1.txt", std::ios::out);

    std::cout << "0 threads" << std::endl;

    for(int i = 100; i <= 1000; i+=100) {
        cout << "matrix " << i << " x " << i << endl;
        Matrix matr_1(i, Vector(i, 0));
        Matrix matr_2(i, Vector(i, 0));

        gener_matrix(matr_1);
        gener_matrix(matr_2);


        result = 0;
        for (int j = 0; j < COUNT_CICLE; j++) {
            Matrix matr_res(i, Vector(i, 0));
            start = std::chrono::system_clock::now();
            mult_matrix_vinograd_optimiz(matr_1, matr_2, matr_res);
            end = std::chrono::system_clock::now();
            result += std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
        }
        result /= COUNT_CICLE;
        write_to_file(file, result);

        cout << "matrix " << i + 1 << " x " << i + 1 << endl;

        matr_1 = Matrix(i + 1, Vector(i + 1, 0));
        matr_2 = Matrix(i + 1, Vector(i + 1, 0));

        gener_matrix(matr_1);
        gener_matrix(matr_2);

        result = 0;
        for (int j = 0; j < COUNT_CICLE; j++) {
            Matrix matr_res(i + 1, Vector(i + 1, 0));
            start = std::chrono::system_clock::now();
            mult_matrix_vinograd_optimiz(matr_1, matr_2, matr_res);
            end = std::chrono::system_clock::now();
            result += std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
        }
        result /= COUNT_CICLE;
        write_to_file(file, result);
    }
    file << std::endl;


    for (int k = 1; k <= 32; k *= 2) {
        cout << k << " threads" << endl;
        for(int i = 100; i <= 1000; i+=100) {
            cout << "matrix " << i << " x " << i << endl;
            Matrix matr_1(i, Vector(i, 0));
            Matrix matr_2(i, Vector(i, 0));

            gener_matrix(matr_1);
            gener_matrix(matr_2);


            result = 0;
            for (int j = 0; j < COUNT_CICLE; j++) {
                Matrix matr_res(i, Vector(i, 0));
                start = std::chrono::system_clock::now();
                mult_matrix_vinograd_optimiz_with_threads(k, matr_1, matr_2, matr_res);
                end = std::chrono::system_clock::now();
                result += std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
            }
            result /= COUNT_CICLE;
            write_to_file(file, result);

            cout << "matrix " << i + 1 << " x " << i + 1 << endl;
            matr_1 = Matrix(i + 1, Vector(i + 1, 0));
            matr_2 = Matrix(i + 1, Vector(i + 1, 0));

            gener_matrix(matr_1);
            gener_matrix(matr_2);

            result = 0;
            for (int j = 0; j < COUNT_CICLE; j++) {
                Matrix matr_res(i + 1, Vector(i + 1, 0));
                start = std::chrono::system_clock::now();
                mult_matrix_vinograd_optimiz_with_threads(k, matr_1, matr_2, matr_res);
                end = std::chrono::system_clock::now();
                result += std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
            }
            result /= COUNT_CICLE;
            write_to_file(file, result);
        }
        file << std::endl;

     }

    file.close();
    std::cout << "OK";


}
