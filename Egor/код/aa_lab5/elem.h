#ifndef ELEM_H
#define ELEM_H

#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <windows.h>

struct Key {
    long int e;
    long int n;
};

struct File_obj {
    int index_str;
    int num_belt;
    SYSTEMTIME t;
    char state;
};

struct Conv_obj {
    int index;
    std::string str;
    std::vector<long long int> vec;
    Key public_key, private_key;
};

//class Elem
//{
//public:
//    Elem(std::string& str_) : str(str_) { }
//    ~Elem() { }
//    std::string& get_str() { return str; }
//    std::chrono::milliseconds get_time(size_t i) {return time[i]; }
//    void set_time(size_t i, std::chrono::milliseconds time_) { time[i] = time_; }
//    void print_time() {
//        for(size_t i = 0; i < 6; i++) {
//            std::cout << std::setw(7) << time[i].count() << " ";
//        }
//        std::cout << std::endl;
//    }

//private:

//};

#endif // ELEM_H
