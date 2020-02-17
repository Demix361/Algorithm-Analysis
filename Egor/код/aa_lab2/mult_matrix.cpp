#include "mult_matrix.h"

void print_matr(Matrix &matr, std::string message) {
    cout << message;
    size_t n = matr.size();
    size_t m = matr[0].size();

    for (size_t i = 0; i < n; i++) {
        for(size_t j = 0; j < m; j++) {
            cout << matr[i][j] << " ";
        }
        cout << endl;
    }
}

int check_matr(Matrix matr_1, Matrix matr_2) {
    size_t n = matr_2.size();
    size_t m = matr_1[0].size();

    if (n != m) {
        return ERROR_SIZE_MATRIX;
    }
    return  SUCCESS;
}

/**
Находит произведение матриц стандартным методом

@param matr_1 [in] - первая матрица
@param matr_2 [in] - вторая матрица
@param res_matr [in] - результирующая матрица
*/
void mult_matrix_std(Matrix matr_1, Matrix matr_2, Matrix &res_matr) {
    size_t m = matr_1.size();
    size_t q = matr_1[0].size();
    size_t n = matr_2[0].size();

    for(size_t i = 0; i < m; i++) {
        for(size_t j = 0; j < n; j++) {
            for(size_t k = 0; k < q; k++) {
                res_matr[i][j] = res_matr[i][j] + matr_1[i][k] * matr_2[k][j];
            }
        }
    }
}

/**
Находит произведение матриц по алгоритму Винограда

@param matr_1 [in] - первая матрица
@param matr_2 [in] - вторая матрица
@param res_matr [in] - результирующая матрица
*/
void mult_matrix_vinograd(Matrix matr_1, Matrix matr_2, Matrix &res_matr) {
    size_t m = matr_1.size();
    size_t q = matr_1[0].size();
    size_t n = matr_2[0].size();

    Vector mul_h(m, 0);
    Vector mul_v(n, 0);

    for(size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < q/2; j++) {
            mul_h[i] = mul_h[i] + matr_1[i][j*2] * matr_1[i][j*2 + 1];
        }
    }


    for(size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < q/2; j++) {
            mul_v[i] = mul_v[i] + matr_2[j*2][i] * matr_2[j*2 + 1][i];
        }
    }

    for(size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            res_matr[i][j] = res_matr[i][j] - mul_h[i] - mul_v[j];
            for(size_t k = 0; k < q/2; k++) {
                res_matr[i][j] = res_matr[i][j] + (matr_1[i][2*k] + matr_2[2*k + 1][j]) *
                                    (matr_1[i][2*k + 1] + matr_2[2*k][j]);
            }

        }
    }

    if (q % 2 == 1) {
        for(size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                res_matr[i][j] = res_matr[i][j] + matr_1[i][q - 1] * matr_2[q - 1][j];
            }
        }
    }
}

/**
Находит произведение матриц по оптимизированному алгоритму Винограда

@param matr_1 [in] - первая матрица
@param matr_2 [in] - вторая матрица
@param res_matr [in] - результирующая матрица
*/
void mult_matrix_vinograd_optimiz(Matrix matr_1, Matrix matr_2, Matrix &res_matr) {
    size_t m = matr_1.size();
    size_t q = matr_1[0].size();
    size_t q2 = q - 1;
    size_t n = matr_2[0].size();

    Vector mul_h(m, 0);
    Vector mul_v(n, 0);

    for(size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < q2; j+=2) {
            mul_h[i] -= matr_1[i][j] * matr_1[i][j + 1];
        }
    }


    for(size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < q2; j+=2) {
            mul_v[i] -= matr_2[j][i] * matr_2[j + 1][i];
        }
    }

    for(size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            res_matr[i][j] = mul_h[i] + mul_v[j];
            int buf = 0;
            for(size_t k = 0; k < q2; k+=2) {
                buf += (matr_1[i][k] + matr_2[k + 1][j]) *
                                    (matr_1[i][k + 1] + matr_2[k][j]);
            }
            res_matr[i][j] += buf;
        }
    }


    if (q % 2 == 1) {
        for(size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                res_matr[i][j] += matr_1[i][q2] * matr_2[q2][j];
            }
        }
    }

}

