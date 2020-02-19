#include "matrix.h"
#include <fstream>
#include <iostream>
Matrix::Matrix(int n, int m)
{
    (*this).n = n;
    (*this).m = m;
    matr = new double*[n];
    for (int i = 0; i < n; i++)
        matr[i] = new double[m];
}

Matrix::Matrix()
{

}

Matrix & Matrix::operator =(const Matrix &matr1)
{
    m = matr1.GetM();
    n = matr1.GetN();
    matr = matr1.matr;
    return *this;
}

Matrix::Matrix(std::istream& os)
{
    os >> n;
    os >> m;
    matr = new double*[n];
    for (int i = 0; i < n; i++)
        matr[i] = new double[m];
    for (int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            os >> matr[i][j];
}

double * Matrix::operator [](int i)
{
    return matr[i];
}

std::ostream& operator <<(std::ostream& os, Matrix & m)
{
    for (int i = 0; i < m.GetN(); i++)
    {
        for(int j = 0; j < m.GetM(); j++)
            os << m[i][j] << " ";
        os << "\n";
    }
    return os;
}

std::ostream& operator <<(std::ostream& os, Matrix m)
{
    for (int i = 0; i < m.GetN(); i++)
    {
        for(int j = 0; j < m.GetM(); j++)
            os << m[i][j] << " ";
        os << "\n";
    }
    return os;
}

 int Matrix::GetN () const
 {
     return n;
 }


 int Matrix::GetM() const
 {
     return m;
 }
