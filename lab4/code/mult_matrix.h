#pragma once

#include <iostream>
#include <vector>
#include <thread>

#define SUCCESS 0
#define ERROR_SIZE_MATRIX -1

using Matrix = std::vector<std::vector<int>>;
using Vector = std::vector<int>;

using std::cout;
using std::cin;
using std::endl;


void mult_matrix_std(Matrix matr_1, Matrix matr_2, Matrix &res_matr);
void mult_matrix_vinograd(Matrix matr_1, Matrix matr_2, Matrix &res_matr);
void mult_matrix_vinograd_optimiz_with_threads(int count_th, Matrix matr_1, Matrix matr_2,
                                  Matrix &res_matr);
void mult_matrix_vinograd_optimiz(Matrix matr_1, Matrix matr_2,
                                  Matrix &res_matr);
void print_matr(Matrix &matr, std::string message);