
#include <ctime>
#include <chrono>
#include <fstream>
#include <cstring>


#include "sort.h"



#define COUNT_CICLE 10000
#define MAX_NUMBER 1000
#define STEP 100



void gener_arr(Vector &arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n; i++) {
        arr[i] = rand();
    }

}

void gener_arr_decrease(Vector &arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n; i++) {
        arr[i] = - int(i);

    }

}

void gener_arr_increase(Vector &arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n; i++) {
        arr[i] = i;

    }
}

void gener_arr_mix(Vector &arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n; i++) {
        if (i%2) {
            arr[i] = i;
        }
        else {
            arr[i] = - int(i);
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

    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::ofstream file_1, file_2, file_3;
    file_1.open("random.txt", std::ios::out);
    file_2.open("heavy.txt", std::ios::out);
    file_3.open("light.txt", std::ios::out);



    for(int i = STEP; i <= MAX_NUMBER; i+=STEP) {
        cout << i << endl;
        Vector arr(i, 0);

        gener_arr(arr);
        file_1 << i << "/";
        result = 0;
        for (int j = 0; j < COUNT_CICLE; j++) {
            Vector res_arr = arr;
            start = std::chrono::system_clock::now();
            bubble_sort(res_arr);
            end = std::chrono::system_clock::now();
            result += std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
        }
        result /= COUNT_CICLE;
        write_to_file(file_1, result);

        result = 0;
        for (int j = 0; j < COUNT_CICLE; j++) {
            Vector res_arr = arr;
            start = std::chrono::system_clock::now();
            quick_sort(res_arr);
            end = std::chrono::system_clock::now();
            result += std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
        }
        result /= COUNT_CICLE;
        write_to_file(file_1, result);

        result = 0;
        for (int j = 0; j < COUNT_CICLE; j++) {
            Vector res_arr = arr;
            start = std::chrono::system_clock::now();
            merge_sort(res_arr);
            end = std::chrono::system_clock::now();
            result += std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
        }
        result /= COUNT_CICLE;
        write_to_file(file_1, result);
        file_1 << std::endl;
    }

    for(int i = STEP; i <= MAX_NUMBER; i+=STEP) {
        cout << i << endl;
        Vector arr(i, 0);

        gener_arr_decrease(arr);
        file_2 << i << "/";
        result = 0;
        for (int j = 0; j < COUNT_CICLE; j++) {
            Vector res_arr = arr;
            start = std::chrono::system_clock::now();
            bubble_sort(res_arr);
            end = std::chrono::system_clock::now();
            result += std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
        }
        result /= COUNT_CICLE;
        write_to_file(file_2, result);

        result = 0;
        for (int j = 0; j < COUNT_CICLE; j++) {
            Vector res_arr = arr;
            start = std::chrono::system_clock::now();
            quick_sort(res_arr);
            end = std::chrono::system_clock::now();
            result += std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
        }
        result /= COUNT_CICLE;
        write_to_file(file_2, result);

        result = 0;
        for (int j = 0; j < COUNT_CICLE; j++) {
            Vector res_arr = arr;
            start = std::chrono::system_clock::now();
            merge_sort(res_arr);
            end = std::chrono::system_clock::now();
            result += std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
        }
        result /= COUNT_CICLE;
        write_to_file(file_2, result);
        file_2 << std::endl;
    }

    for(int i = STEP; i <= MAX_NUMBER; i+=STEP) {
        cout << i << endl;
        Vector arr(i, 0);

        gener_arr_increase(arr);
        file_3 << i << "/";
        result = 0;
        for (int j = 0; j < COUNT_CICLE; j++) {
            Vector res_arr = arr;
            start = std::chrono::system_clock::now();
            bubble_sort(res_arr);
            end = std::chrono::system_clock::now();
            result += std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
        }
        result /= COUNT_CICLE;
        write_to_file(file_3, result);

        gener_arr(arr);
        result = 0;
        for (int j = 0; j < COUNT_CICLE; j++) {
            Vector res_arr = arr;
            start = std::chrono::system_clock::now();
            quick_sort(res_arr);
            end = std::chrono::system_clock::now();
            result += std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
        }
        result /= COUNT_CICLE;
        write_to_file(file_3, result);

        gener_arr_mix(arr);
        result = 0;
        for (int j = 0; j < COUNT_CICLE; j++) {
            Vector res_arr = arr;
            start = std::chrono::system_clock::now();
            merge_sort(res_arr);
            end = std::chrono::system_clock::now();
            result += std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
        }
        result /= COUNT_CICLE;
        write_to_file(file_3, result);
        file_3 << std::endl;
    }

//    for(int i = 101; i <= 1001; i+=100) {
//        cout << i << endl;
//        test_str += mas;
//        Matrix matr_1(i, Vector(i, 0));
//        Matrix matr_2(i, Vector(i, 0));

//        gener_matrix(matr_1);
//        gener_matrix(matr_2);
//        file << i << "/";
//        result = 0;
//        for (int j = 0; j < COUNT_CICLE; j++) {
//            Matrix matr_res(i, Vector(i, 0));
//            start_time =  clock();
//            mult_matrix_std(matr_1, matr_2, matr_res);
//            end_time =  clock();
//            result += double(end_time - start_time);
//        }
//        result /= COUNT_CICLE;
//        write_to_file(file, result);

//        result = 0;
//        for (int j = 0; j < COUNT_CICLE; j++) {
//            Matrix matr_res(i, Vector(i, 0));
//            start_time =  clock();
//            mult_matrix_vinograd(matr_1, matr_2, matr_res);
//            end_time =  clock();
//            result += double(end_time - start_time);
//        }
//        result /= COUNT_CICLE;
//        write_to_file(file, result);

//        result = 0;
//        for (int j = 0; j < COUNT_CICLE; j++) {
//            Matrix matr_res(i, Vector(i, 0));
//            start_time =  clock();
//            mult_matrix_vinograd_optimiz(matr_1, matr_2, matr_res);
//            end_time =  clock();
//            result += double(end_time - start_time);
//        }
//        result /= COUNT_CICLE;
//        write_to_file(file, result);
//        file << std::endl;

    file_1.close();
    file_2.close();
    file_3.close();
    std::cout << "OK";


}
