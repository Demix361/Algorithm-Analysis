#include "kmp_search.h"

std::vector<int> get_shift(const std::string &str) {
    int len = str.length();
    std::vector<int> shift(len, 0);

    for (int i = 1, j = 0; i < len; ++i) {
        while (j > 0 && str[i] != str[j]) {
            j = shift[j - 1];
        }

        if (str[i] == str[j]) {
            ++j;
        }

        shift[i] = j;
    }

    return shift;
}

int kmp_search(const std::string &text, const std::string &pattern) {
    if (!pattern.length() || text.length() < pattern.length()) {
        return WRONG_LEN;
    }

    const int text_len = text.length();
    const int pattern_len = pattern.length();

    auto shift = get_shift(pattern);

    for (int i = 0, j = 0; i < text_len; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = shift[j - 1];
        }

        if (text[i] == pattern[j]) {
            ++j;
        }

        if (pattern_len == j) {
            return i - pattern_len + 1;
        }
    }

    return NOT_FOUND;
}
