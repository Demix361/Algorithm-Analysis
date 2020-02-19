#include "levenshtein.h"

using Matrix = std::vector<std::vector<int>>;
using Vector = std::vector<int>;
using std::string;
using std::cout, std::cin, std::endl;
using std::min;

void print_matr(Matrix matr, string source_word, string check_word) {
    size_t n = source_word.size() + 1;
    size_t m = check_word.size() + 1;
    cout << "    ";
    for(size_t i = 1; i < m; i++) {
        cout << check_word[i - 1] << " ";
    }
    cout << endl;

    for (size_t i = 0; i < n; i++) {
        if (i > 0)
            cout << source_word[i - 1] << " ";
        else
            cout << "  ";
        for(size_t j = 0; j < m; j++) {
            cout << matr[i][j] << " ";
        }
        cout << endl;
    }
}


/**
Находит расстояние Левенштейна с помощью матрицы

@param source_word [in] - исходная строка
@param check_word [in] - проверяемая строка

@return Возвращает расстояние Левенштейна
*/
int lev_matr_dist(string source_word, string check_word) {
    size_t n = source_word.size() + 1;
    size_t m = check_word.size() + 1;
    Matrix matr(n, Vector(m, 0));

    for(size_t i = 1; i < n; i++) {
        matr[i][0] = matr[i - 1][0] + 1;
    }

    for(size_t i = 1; i < m; i++) {
        matr[0][i] = matr[0][i - 1] + 1;
    }

    int t = 0;
    for (size_t i = 1; i < n; i++) {
        for(size_t j = 1; j < m; j++) {
            source_word[i - 1] == check_word[j - 1] ? t = 0 : t = 1;
            matr[i][j] = min(min(matr[i - 1][j] + 1, matr[i][j - 1] + 1),
                    matr[i - 1][j - 1] + t);
        }
    }

#ifdef RELEASE
    print_matr(matr, source_word, check_word);
#endif

    return matr[n - 1][m - 1];
}

/**
Находит расстояние Дамерау-Левенштейна с помощью матрицы

@param source_word [in] - исходная строка
@param check_word [in] - проверяемая строка

@return Возвращает расстояние Дамерау-Левенштейна
*/
int dam_lev_matr_dist(string source_word, string check_word) {
    size_t n = source_word.size() + 1;
    size_t m = check_word.size() + 1;
    Matrix matr(n, Vector(m, 0));

    for(size_t i = 1; i < n; i++) {
        matr[i][0] = matr[i - 1][0] + 1;
    }

    for(size_t i = 1; i < m; i++) {
        matr[0][i] = matr[0][i - 1] + 1;
    }

    int t = 0;

    for (size_t i = 1; i < n; i++) {
        for(size_t j = 1; j < m; j++) {
            t = 0;
            source_word[i - 1] == check_word[j - 1] ? t = 0 : t = 1;
            matr[i][j] = min(min(matr[i - 1][j] + 1, matr[i][j - 1] + 1),
                    matr[i - 1][j - 1] + t);

            if (i > 1 && j > 1 && source_word[i - 1] == check_word[j - 2] &&
                    source_word[i - 2] == check_word[j - 1]) {
                matr[i][j] = min(matr[i][j], matr[i - 2][j - 2] + t);
            }
        }
    }

#ifdef RELEASE
    print_matr(matr, source_word, check_word);
#endif
    return matr[n - 1][m - 1];
}

/**
Рекурсивно находит расстояние Дамерау-Левенштейна

@param source_word [in] - исходная строка
@param check_word [in] - проверяемая строка

@return Возвращает расстояние Дамерау-Левенштейна
*/
int dam_lev_rec_dist(string source_word, string check_word) {

    size_t n = source_word.size();
    size_t m = check_word.size();

    if (!n) {
        return m;
    }
    if (!m) {
        return n;
    }

    int t = 0;
    source_word[n - 1] == check_word[m - 1] ? t = 0 : t = 1;

    int ins = dam_lev_rec_dist(source_word, check_word.substr(0, m - 1)) + 1;
    int del = dam_lev_rec_dist(source_word.substr(0, n - 1), check_word) + 1;
    int rep = dam_lev_rec_dist(source_word.substr(0, n - 1),
                               check_word.substr(0, m - 1)) + t;
    int per = std::numeric_limits<short>::max();

    if (n > 1 && m > 1 && source_word[n - 1] == check_word[m - 2] &&
            source_word[n - 2] == check_word[m - 1]) {
        per = dam_lev_rec_dist(source_word.substr(0, n - 2),
                                         check_word.substr(0, m - 2)) + t;
    }

    return min(min(min(ins, del), rep), per);

}

