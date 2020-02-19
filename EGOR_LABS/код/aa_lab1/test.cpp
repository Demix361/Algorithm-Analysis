#include "levenshtein.h"

#define COUNT_TESTS 20
std::vector<std::vector<std::string>> string = {{"", ""},
                                                {"a", ""},
                                                {"", "a"},
                                                {"a", "b"},
                                                {"skat", "kot"},
                                                {"red", "erd"},
                                                {"student", "sutednt"},
                                                {"mouse", "mouse"},
                                                {"relevant", "elephant"},
                                                {"abc", "def"},
                                                {"coffee", "soda"},
                                                {"annas", "max"},
                                                {"levenshtein", "meilenstein"},
                                                {"notebook", "ontbeooko"},
                                                {"market", "street"},
                                                {"ball", "ballon"},
                                                {"bbball", "ball"},
                                                {"doctor", "odtcor"},
                                                {"factory", "fcatroy"},
                                                {"park", "krap"}};

std::vector<std::vector<int>> answer = {{0, 0},
                                        {1, 1},
                                        {1, 1},
                                        {1, 1},
                                        {2, 2},
                                        {2, 1},
                                        {3, 2},
                                        {0, 0},
                                        {3, 3},
                                        {3, 3},
                                        {5, 5},
                                        {4, 4},
                                        {4, 4},
                                        {5, 3},
                                        {3, 3},
                                        {2, 2},
                                        {2, 2},
                                        {3, 2},
                                        {4, 2},
                                        {4, 3}};

void tests() {
    int count_success = 0;
    int res_lev_matr = 0, res_dam_lev_matr = 0, res_dam_lev_rec = 0;
    for(int i = 0; i < COUNT_TESTS; i++) {
        res_lev_matr = lev_matr_dist(string[i][0], string[i][1]);
        res_dam_lev_matr = dam_lev_matr_dist(string[i][0], string[i][1]);
        res_dam_lev_rec = dam_lev_rec_dist(string[i][0], string[i][1]);

        std::cout << "[" << string[i][0] << "] [" << string[i][1] << "]" << std::endl
                  << "Answer: Levenshtein - " << answer[i][0] << ", Damerau-Levenshtein - " << answer[i][1] << std::endl
                  << "Result: Levenshtein matrix - " << res_lev_matr
                  << ", Damerau-Levenshtein  matrix - " << res_dam_lev_matr
                  << ", Damerau-Levenshtein  recursion - " << res_dam_lev_rec << std::endl;
        if (res_lev_matr == answer[i][0] && res_dam_lev_matr == answer[i][1] &&
                res_dam_lev_rec == answer[i][1]) {
            count_success++;
            std::cout << "Test OK!" << std::endl;
        }
        else
            std::cout << "Test FAILED!" << std::endl;

    }

    std::cout << "Tests success: " << count_success << "/" << COUNT_TESTS << std::endl;
}

int main(int argc, char *argv[])
{
   tests();
   //metering();

   return 0;
}

