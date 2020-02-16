#ifndef ELEM_H
#define ELEM_H

#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <windows.h>


struct Key
{
    long int e;
    long int n;
};


struct File_obj
{
    int index_str;
    int num_belt;
    SYSTEMTIME t;
    char state;
};


struct Conv_obj
{
    int index;
    std::string str;
    std::vector<long long int> vec;
    Key public_key, private_key;
};


#endif // ELEM_H
