#include "sort.h"


void merge(Vector &arr, size_t st1, size_t end1, size_t end2, Vector &tmp) {
    size_t st2 = end1 + 1;
    size_t fin_st = st1;
    size_t fin_end = end2;
    size_t index = 0;
    while (st1 <= end1 && st2 <= end2) {
        if (arr[st1] < arr[st2]) {
            tmp[index] = arr[st1];
            st1++;
        }
        else {
            tmp[index] = arr[st2];
            st2++;
        }
        index++;
    }

    if (st1 <= end1) {
        for (size_t i = st1; i <= end1; i++, index++) {
            tmp[index] = arr[i];
        }
    }
    else {
        for (size_t i = st2; i <= end2; i++, index++) {
            tmp[index] = arr[i];
        }
    }

    index = 0;
    for (size_t i = fin_st; i <= fin_end; i++, index++) {
        arr[i] = tmp[index];
    }


}
void _merge_sort(Vector &arr, size_t l, size_t r, Vector &tmp) {
    if (l == r) return;
    size_t m = (l + r) / 2;
    _merge_sort(arr, l, m, tmp);
    _merge_sort(arr, m + 1, r, tmp);
    merge(arr, l, m, r, tmp);
}

void merge_sort(Vector &arr) {
    size_t l = 0;
    size_t r = arr.size() - 1;
    Vector tmp(r + 1, 0);
    _merge_sort(arr, l, r, tmp);
}

void bubble_sort(Vector &arr) {
    size_t n = arr.size();
    double tmp = 0;
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}


size_t pivot_arr(Vector &arr, size_t l, size_t r) {

    double pivot_value = arr[l];
    size_t pivot_point = l;
    for (size_t i = l + 1; i <= r; i++) {
        if (arr[i] < pivot_value) {
            pivot_point++;
            std::swap(arr[pivot_point], arr[i]);
        }
    }
    std::swap(arr[l], arr[pivot_point]);
    return pivot_point;

}

void _quick_sort(Vector &arr, size_t l, size_t r) {
    if (r == l) return;
    size_t pivot = pivot_arr(arr, l, r);
    if (l < pivot) {
        _quick_sort(arr, l, pivot - 1);
    }
    if (r > pivot) {
        _quick_sort(arr, pivot + 1, r);
    }
}


void quick_sort(Vector &arr) {
    size_t l = 0;
    size_t r = arr.size() - 1;
    _quick_sort(arr, l, r);
}




