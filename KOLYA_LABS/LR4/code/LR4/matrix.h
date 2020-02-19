#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <stdarg.h>
#include <memory>
#include <vector>
#include <fstream>



class Matrix
{
public:
    Matrix(int n, int m);
    Matrix(std::istream& os);
    std::ostream& operator <<(std::ostream& os);
    Matrix &operator =(const Matrix &m);
    double * operator [](int i);
    int GetN() const;
    int GetM() const;
    Matrix();
private:
    int n;
    int m;
    double **matr;
};
std::ostream& operator <<(std::ostream& os, Matrix & m);
#endif // MATRIX_H
