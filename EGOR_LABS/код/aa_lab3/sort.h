#pragma once

#include <iostream>
#include <vector>

#define SUCCESS 0
#define ERROR_SIZE_MATRIX -1


using Vector = std::vector<double>;

using std::cout, std::cin, std::endl;


void merge_sort(Vector &);
void bubble_sort(Vector &);
void quick_sort(Vector &);
