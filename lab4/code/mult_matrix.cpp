#include "mult_matrix.h"
#include <thread>


void print_matr(Matrix &matr, std::string message)
{
    cout << message;
    size_t n = matr.size();
    size_t m = matr[0].size();

    for (size_t i = 0; i < n; i++)
    {
        for(size_t j = 0; j < m; j++)
        {
            cout << matr[i][j] << " ";
        }
        cout << endl;
    }
}


int check_matr(Matrix matr_1, Matrix matr_2)
{
    size_t n = matr_2.size();
    size_t m = matr_1[0].size();

    if (n != m)
    {
        return ERROR_SIZE_MATRIX;
    }
    return  SUCCESS;
}



void calc_mul_h(Matrix &matr_1, size_t m, size_t q2, Vector &mul_h)
{
    for(size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < q2; j+=2)
        {
            mul_h[i] -= matr_1[i][j] * matr_1[i][j + 1];
        }
    }
}


void calc_mul_v(Matrix &matr_2, size_t n, size_t q2, Vector &mul_v)
{
    for(size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < q2; j+=2)
        {
            mul_v[i] -= matr_2[j][i] * matr_2[j + 1][i];
        }
    }
}


void calc_in_if(Matrix &matr_1, Matrix &matr_2, Matrix &res_matr, size_t start, size_t step)
{
    size_t m = matr_1.size();
    size_t q2 = matr_1[0].size() - 1;
    size_t n = matr_2[0].size();

    for(size_t i = start; i < m; i += step)
    {
        for (size_t j = 0; j < n; j++)
        {
            res_matr[i][j] += matr_1[i][q2] * matr_2[q2][j];
        }
    }
}


void calc_mult(Vector &mul_h, Vector &mul_v, Matrix &matr_1, Matrix &matr_2,
               Matrix &res_matr, size_t start, size_t step)
{
    size_t m = matr_1.size();
    size_t q2 = matr_1[0].size() - 1;
    size_t n = matr_2[0].size();

    for(size_t i = start; i < m; i += step)
    {
        for (size_t j = 0; j < n; j++)
        {
            res_matr[i][j] = mul_h[i] + mul_v[j];
            int buf = 0;
            for(size_t k = 0; k < q2; k+=2)
            {
                buf += (matr_1[i][k] + matr_2[k + 1][j]) *
                                    (matr_1[i][k + 1] + matr_2[k][j]);
            }
            res_matr[i][j] += buf;
        }
    }
}


void mult_matrix_vinograd_optimiz_with_threads(int count_th, Matrix matr_1, Matrix matr_2, Matrix &res_matr)
{
    size_t m = matr_1.size();
    size_t q = matr_1[0].size();
    size_t q2 = q - 1;
    size_t n = matr_2[0].size();

    Vector mul_h(m, 0);
    Vector mul_v(n, 0);

    std::thread thread_1(calc_mul_h, std::ref(matr_1), m, q2, std::ref(mul_h));
    std::thread thread_2(calc_mul_v, std::ref(matr_2), n, q2, std::ref(mul_v));
    thread_1.join();
    thread_2.join();

    std::vector<std::thread> thread_arr(count_th);

    for(int i = 0; i < count_th; i++)
    {
        thread_arr[i] = std::thread(calc_mult, std::ref(mul_h),
                                    std::ref(mul_v), std::ref(matr_1),
                                    std::ref(matr_2), std::ref(res_matr),
                                    i, count_th);
    }

    for(int i = 0; i < count_th; i++)
    {
        thread_arr[i].join();
    }


    if (q % 2 == 1)
    {
        for(int i = 0; i < count_th; i++)
        {
            thread_arr[i] = std::thread(calc_in_if, std::ref(matr_1),
                                        std::ref(matr_2), std::ref(res_matr),
                                        i, count_th);
        }

        for(int i = 0; i < count_th; i++)
        {
            thread_arr[i].join();
        }
    }
}


void mult_matrix_vinograd_optimiz(Matrix matr_1, Matrix matr_2, Matrix &res_matr)
{
    size_t m = matr_1.size();
    size_t q = matr_1[0].size();
    size_t q2 = q - 1;
    size_t n = matr_2[0].size();

    Vector mul_h(m, 0);
    Vector mul_v(n, 0);

    for(size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < q2; j+=2)
        {
            mul_h[i] -= matr_1[i][j] * matr_1[i][j + 1];
        }
    }


    for(size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < q2; j+=2)
        {
            mul_v[i] -= matr_2[j][i] * matr_2[j + 1][i];
        }
    }

    for(size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            res_matr[i][j] = mul_h[i] + mul_v[j];
            int buf = 0;
            for(size_t k = 0; k < q2; k+=2)
            {
                buf += (matr_1[i][k] + matr_2[k + 1][j]) *
                                    (matr_1[i][k + 1] + matr_2[k][j]);
            }
            res_matr[i][j] += buf;
        }
    }


    if (q % 2 == 1)
    {
        for(size_t i = 0; i < m; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                res_matr[i][j] += matr_1[i][q2] * matr_2[q2][j];
            }
        }
    }
}
