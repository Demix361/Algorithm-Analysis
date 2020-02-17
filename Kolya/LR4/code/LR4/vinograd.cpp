#include "matrix.h"
#include "vinograd.h"
#include <thread>
#include <malloc.h>

Matrix Vinograd(Matrix& matr1, Matrix& matr2)
{
    int n = matr1.Matrix::GetN();
    int m = matr2.Matrix::GetM();
    int m1 = matr1.Matrix::GetM();
    double *mulh = new double[n];
    double *mulv = new double[m];

    Matrix res = Matrix(n, m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m1/2; j++)
        {
            mulh[i] = mulh[i] + matr1[i][2*j] * matr1[i][2*j + 1];
        }
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m1/2; j++)
            mulv[i] = mulv[i] + matr2[2*j][i] * matr2[2*j + 1][i];


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            res[i][j] = - mulh[i] - mulv[j];
            for (int k = 0; k < m1/2; k++)
                res[i][j] = res[i][j] + (matr1[i][2*k]+matr2[2*k+1][j])*(matr1[i][2*k+1]+matr2[2*k][j]);
        }
    }

    if (m1 % 2)
    {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                res[i][j] = res[i][j] + matr1[i][m1 - 1] * matr2[m1 - 1][j];
    }
    return res;
}

void func_thread(Matrix &matr1, Matrix &matr2, Matrix &res,  double* mulh,  double* mulv, int num, int count)
{
    for(int i = num; i < matr1.Matrix::GetN(); i += count)
    {
        for(int j = 0; j < matr2.Matrix::GetM(); j++)
        {
            res[i][j] = res[i][j] - mulh[i] - mulv[j];
            for(int k = 0; k < matr1.Matrix::GetM() / 2; k++)
            {
                res[i][j] = res[i][j] + (matr1[i][2*k] + matr2[2*k+1][j]) * (matr1[i][2*k + 1] + matr2[2*k][j]);
            }
        }
    }
}

Vinograd_data::Vinograd_data()
{

}

Vinograd_data * Vinograd_1(Vinograd_data * v)
{
    int n = v->matr1.GetN();
    int m = v->matr2.GetM();
    int m1 = v->matr1.Matrix::GetM();
    double *mulh = new double[n];
    double *mulv = new double[m];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m1/2; j++)
            mulh[i] = mulh[i] + v->matr1[i][2*j] * v->matr1[i][2*j + 1];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m1/2; j++)
            mulv[i] = mulv[i] + v->matr2[2*j][i] * v->matr2[2*j + 1][i];
    v->mulh = mulh;
    v->mulv = mulv;
    return v;
}

Vinograd_data * Vinograd_2(Vinograd_data * v)
{

    int n = v->matr1.GetN();
    int m = v->matr2.GetM();
    int m1 = v->matr1.Matrix::GetM();
    v->res = Matrix(n, m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            v->res[i][j] = - v->mulh[i] - v->mulv[j];
            for (int k = 0; k < m1/2; k++)
                v->res[i][j] = v->res[i][j] + (v->matr1[i][2*k]+v->matr2[2*k+1][j])*(v->matr1[i][2*k+1]+v->matr2[2*k][j]);
        }
    }
    return v;
}

Vinograd_data * Vinograd_3(Vinograd_data * v)
{
    int n = v->matr1.Matrix::GetN();
    int m = v->matr2.Matrix::GetM();
    int m1 = v->matr1.Matrix::GetM();
    if (m1 % 2)
    {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                v->res[i][j] = v->res[i][j] + v->matr1[i][m1 - 1] * v->matr2[m1 - 1][j];
    }
    return v;
}

Matrix Vinograd_Parallell1(Matrix& matr1, Matrix& matr2, int count)
{
    int n = matr1.Matrix::GetN();
    int m = matr2.Matrix::GetM();
    int m1 = matr1.Matrix::GetM();
    double *mulh = new double[n];
    double *mulv = new double[m];

    Matrix res = Matrix(n, m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m1/2; j++)
        {
            mulh[i] = mulh[i] + matr1[i][2*j] * matr1[i][2*j + 1];
        }
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m1/2; j++)
            mulv[i] = mulv[i] + matr2[2*j][i] * matr2[2*j + 1][i];

    std::thread threads[count];

    for(int i = 0; i < count; i++)
        threads[i] = std::thread(func_thread, std::ref(matr1), std::ref(matr1), std::ref(res), mulh, mulv, i, count);

    for(int i = 0; i < count; i++)
        if(threads[i].joinable())
            threads[i].join();

    if (m1 % 2)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                res[i][j] = res[i][j] + matr1[i][m1 - 1] * matr2[m1 - 1][j];
    delete[] mulh;
    delete[] mulv;
    return res;
}

void Get_Mulh(Matrix& matr1, double *mulh, int i, int count)
{
    int n = matr1.Matrix::GetN();
    int m1 = matr1.Matrix::GetM();

    for (; i < n; i += count)
        for (int j = 0; j < m1/2; j++)
        {
            mulh[i] = mulh[i] + matr1[i][2*j] * matr1[i][2*j + 1];
        }

}

void Get_Mulv(Matrix& matr1, Matrix& matr2, double *mulv, int i, int count)
{
    int m = matr2.Matrix::GetM();
    int m1 = matr1.Matrix::GetM();
    for (; i < m; i += count)
        for (int j = 0; j < m1/2; j++)
            mulv[i] = mulv[i] + matr2[2*j][i] * matr2[2*j + 1][i];
}

void func_thread2(Matrix& matr1, Matrix& matr2, Matrix& res, int i, int count)
{
    int n = matr1.Matrix::GetN();
    int m = matr2.Matrix::GetM();
    int m1 = matr1.Matrix::GetM();

    for(; i < n; i += count)
        for(int j = 0; j < m; j++)
            res[i][j] = res[i][j] + matr1[i][m1 - 1] * matr2[m1 - 1][j];
}



Matrix Vinograd_Parallell2(Matrix& matr1, Matrix& matr2, int count)
{
    int n = matr1.Matrix::GetN();
    int m = matr2.Matrix::GetM();
    int m1 = matr1.Matrix::GetM();
    double * mulh = new double[n];
    double * mulv = new double[m];
    for (int i = 0; i < n; i++)
        mulh[i] = 0;
    for (int i = 0; i < m; i++)
        mulv[i] = 0;


    Matrix res = Matrix(n, m);

    if (m1 % 2)
    {

        int count1 = (count + (count % 4)? (4 - count % 4) : 0)/4;
        std::thread t1[count1];
        std::thread t2[count1];
        std::thread t3[count1*2];
        for(int i = 0; i < count1; i++)
        {
            t1[i] = std::thread(Get_Mulh, std::ref(matr1), mulh, i, count1);
            t2[i] = std::thread(Get_Mulv, std::ref(matr1), std::ref(matr2), mulv, i, count1);
        /*    if(t1[i].joinable())
                t1[i].join();
            if(t2[i].joinable())
                t2[i].join();
        }
        for(int i = 0; i < count1 * 2; i++)
        {
            t3[i] = std::thread(func_thread2, std::ref(matr1), std::ref(matr2), std::ref(res), i, count1*2);
            if(t3[i].joinable())
                t3[i].join();
        }*/
        }
        for(int i = 0; i < count1 * 2; i++)
        {
            t3[i] = std::thread(func_thread2, std::ref(matr1), std::ref(matr2), std::ref(res), i, count1*2);
        }
        for(int i = 0; i < count1; i++)
        {
            if(t1[i].joinable())
                t1[i].join();
            if(t2[i].joinable())
                t2[i].join();
        }
        for(int i = 0; i < count1 * 2; i++)
        {
            if(t3[i].joinable())
                t3[i].join();
        }
    }
    else
    {
        int count1 = (count + ((count % 2)? 1 : 0))/2;
        std::thread t1[count1];
        std::thread t2[count1];

        for(int i = 0; i < count1; i++)
        {
            t1[i] = std::thread(Get_Mulh, std::ref(matr1), mulh, i, count1);
            t2[i] = std::thread(Get_Mulv, std::ref(matr1), std::ref(matr2), mulv, i, count1);
        }
        for(int i = 0; i < count1; i++)
        {
            if(t1[i].joinable())
                t1[i].join();
            if(t2[i].joinable())
                t2[i].join();
        }
    }
    std::thread threads[count];

    for(int i = 0; i < count; i++)
        threads[i] = std::thread(func_thread, std::ref(matr1), std::ref(matr1), std::ref(res), &mulh[0], &mulv[0], i, count);

    for(int i = 0; i < count; i++)
        if(threads[i].joinable())
            threads[i].join();
    delete[] mulh;
    delete[] mulv;
    return res;
}
