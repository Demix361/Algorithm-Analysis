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
    Matrix();
    Matrix(int n, int m);
    Matrix(int n, int m, double value);
    Matrix(std::istream& os);
    std::ostream& operator <<(std::ostream& os);
    Matrix & operator =(const Matrix &m);
    Matrix & operator +=(Matrix & mat);
    double * operator [](int i);
    int GetN() const;
    int GetM() const;
private:
    int n;
    int m;
    double **matr;
};
std::ostream& operator <<(std::ostream& os, Matrix & m);
#endif // MATRIX_H
