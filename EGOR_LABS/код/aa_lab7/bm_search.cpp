#include "bm_search.h"
#include "print.h"

int bm_search(const std::string &text, const std::string &pattern) {
    if (!pattern.length() || text.length() < pattern.length()) {
        return WRONG_LEN;
    }

    const int text_len = text.length();
    const int pattern_len = pattern.length();
    const int dif_len = text_len - pattern_len;

    const int ascii_num = 256;
    std::vector<int> stop_table(ascii_num, -1);
    std::vector<int> shift_table(pattern_len);

    for (int i = 0; i < pattern_len; ++i) {
        stop_table[pattern[i]] = i;
    }

    std::string rev_pattern(pattern.rbegin(), pattern.rend());
    auto suffix_table = get_shift(pattern);
    auto prefix_table = get_shift(rev_pattern);

    for (int i = 0; i < pattern_len; ++i) {
        shift_table[i] = pattern_len - suffix_table.back();
    }

    for (int i = 1; i < pattern_len; ++i) {
        int j = prefix_table[i];
        shift_table[i] = std::max(shift_table[j], i - prefix_table[i] + 1);
    }

    int shift = 0;
    while (shift <= dif_len) {
        int pos = pattern_len - 1;

        while (text[pos + shift] == pattern[pos]) {
            if (0 == pos) {
                return shift;
            }

            --pos;
        }

        if (pattern_len - 1 == pos) {
            int stop_symb = pos;

            if (pos + shift < ascii_num) {
                stop_symb -= stop_table[text[pos + shift]];
            } else {
               ++stop_symb;
            }

            shift += stop_symb;
        } else {
            shift += shift_table[pattern_len - pos - 1];
        }
    }

    return NOT_FOUND;
}
