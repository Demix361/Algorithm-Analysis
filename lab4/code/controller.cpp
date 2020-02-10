#include "controller.h"
#include "mult_matrix.h"

using Matrix = std::vector<std::vector<int>>;
using Vector = std::vector<int>;
using std::string;
using std::cout;
using std::cin;
using std::endl;

int enter_int(std::string message) {
    int number;

    char answer[256];
    cout << message;
    fgets(answer, sizeof(answer), stdin); // считываем строку

    while (sscanf(answer, "%d", &number) != 1 || number <= 0) {
        printf("Incorrect input. Try again: ");
        fgets(answer, sizeof(answer), stdin);
    }
    return number;
}

int enter_int_2(std::string message) {
    int number;

    char answer[256];
    cout << message;
    fgets(answer, sizeof(answer), stdin); // считываем строку

    while (sscanf(answer, "%d", &number) != 1) {
        printf("Incorrect input. Try again: ");
        fgets(answer, sizeof(answer), stdin);
    }
    return number;
}

// double enter_double() {
//     double number;
//     char answer[256];
//     fgets(answer, sizeof(answer), stdin); // считываем строку

//     while (sscanf(answer, "%f", &number) != 1) {
//         printf("Incorrect input. Try again: ");
//         fgets(answer, sizeof(answer), stdin);
//     }
//     return number;
// }

void enter_matr(Matrix &matr) {

    size_t n = matr.size();
    size_t m = matr[0].size();

    for (size_t i = 0; i < n; i++) {
        for(size_t j = 0; j < m; j++) {
            cout << "matr[" << i << "][" << j << "] = ";
            matr[i][j] = enter_int_2("");
        }
    }
}



void controller() {
    std::string source_word, check_word;
    int m = 0, n = 0, q = 0;
    int count_th = 0;

    n = enter_int("Enter number of matrix_1 rows: ");
    m = enter_int("Enter number of matrix_1 columns: ");

    Matrix matr_1(n, Vector(m, 0));
    enter_matr(matr_1);
    print_matr(matr_1, "standard:\n");
    q = enter_int("Enter number of matrix 2 columns: ");
    Matrix matr_2(m, Vector(q, 0));
    enter_matr(matr_2);
    Matrix res_matr_1(n, Vector(q, 0));
    Matrix res_matr_2(n, Vector(q, 0));
    Matrix res_matr_3(n, Vector(q, 0));

    count_th = enter_int("Enter count threads: ");
    print_matr(matr_1, "Matrix 1: \n");
    print_matr(matr_2, "Matrix 2:\n");

    mult_matrix_vinograd_optimiz_with_threads(count_th, matr_1, matr_2, res_matr_3);
    print_matr(res_matr_3, "Result of multiplication by Vinograd is optimized:\n");


}
