#include <vector>
#include <random>
#include <algorithm>
#include "total_search.h"


#include <iostream>
#include "print.h"

double total_search(Matrix matrix, std::vector<int> &way) {
    int n = matrix.size();
    double min_len = -1;

    std::vector<int> p(n);  // permutation
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
  
    do {
        int len = 0;

        for (int i = 0; i < n - 1; ++i) {
            len += matrix[p[i]][p[i + 1]];
        }

        len += matrix[p[n - 1]][p[0]];
        if (len < min_len || min_len < 0) {
            min_len = len;
            for (int i = 0; i < n; ++i) {
                way[i] = p[i];
            }
        }
    } while(std::next_permutation(p.begin(), p.end()));

    return min_len;
}
