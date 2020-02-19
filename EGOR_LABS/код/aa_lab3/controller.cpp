#include "controller.h"
#include "sort.h"


using std::string;
using std::cout, std::cin, std::endl;


int enter_int(std::string message, int beg, int end) {
    int number;

    char answer[256];
    cout << message;
    fgets(answer, sizeof(answer), stdin); // считываем строку

    while (sscanf(answer, "%d", &number) != 1 || number < beg || number > end) {
        printf("Incorrect input. Try again: ");
        fgets(answer, sizeof(answer), stdin);
    }
    return number;
}

int enter_int(std::string message) {
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

double enter_double(std::string message, double beg, double end) {
    int number;

    char answer[256];
    cout << message;
    fgets(answer, sizeof(answer), stdin); // считываем строку

    while (sscanf(answer, "%f", &number) != 1 || number - beg || number > end) {
        printf("Incorrect input. Try again: ");
        fgets(answer, sizeof(answer), stdin);
    }
    return number;
}



void enter_arr(Vector &arr) {

    size_t n = arr.size();

    for (size_t i = 0; i < n; i++) {
        cout << "matr[" << i << "] = ";
        arr[i] = enter_int("");
    }
}




void print_arr(Vector &matr, std::string message) {
    cout << message;
    size_t n = matr.size();

    for (size_t i = 0; i < n; i++) {
        cout << matr[i] << " ";
    }
    cout << endl;
}

void controller() {
    std::string source_word, check_word;
    int m = 0, n = 0, q = 0;

    n = enter_int("Enter number of array: ", 0, 2147483647);

    Vector arr(n, 0);
    enter_arr(arr);

    Vector res_arr_1 = arr;
    Vector res_arr_2 = arr;
    Vector res_arr_3 = arr;


    print_arr(arr, "Source array:");

    bubble_sort(res_arr_1);
    print_arr(res_arr_1, "Result of bubble sort:\n");

    quick_sort(res_arr_1);
    print_arr(res_arr_1, "Result of quick sort:\n");

    merge_sort(res_arr_1);
    print_arr(res_arr_1, "Result of merge sort:\n");



}
