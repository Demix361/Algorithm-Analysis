#ifndef VINOGRAD_H
#define VINOGRAD_H
#include "matrix.h"

Matrix Vinograd(Matrix & matr1, Matrix & matr2);
Matrix Vinograd_Parallell1(Matrix& matr1, Matrix& matr2, int count);
Matrix Vinograd_Parallell2(Matrix& matr1, Matrix& matr2, int count);


struct Vinograd_data
{
    Matrix matr1;
    Matrix matr2;
    double *mulh;
    double *mulv;
    Matrix res;
    Vinograd_data();
};

Vinograd_data *Vinograd_1(Vinograd_data * v);
Vinograd_data *Vinograd_2(Vinograd_data * v);
Vinograd_data *Vinograd_3(Vinograd_data * v);

#endif // VINOGRAD_H
