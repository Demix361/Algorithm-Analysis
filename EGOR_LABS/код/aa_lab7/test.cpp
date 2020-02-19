#include <iostream>
#include "const.h"
#include "kmp_search.h"
#include "bm_search.h"
#include "print.h"


#define COUNT_TESTS 20

std::vector<std::string> text = {"a",
                                "abc",
                                "abc",
                                "abc",
                                "abbaabbab",
                                "abc",
                                "abbaabbab",
                                "abc",
                                "abbaabbab",
                                "there they are",
                                "abc",
                                "abbaabbab",
                                "there they are",
                                "abcabc",
                                "abcabc",
                                "abbaabbabbbab",
                                "there they are are here are",
                                "a",
                                "abc",
                                "abbaabbabbbab"
                                };



std::vector<std::string> pattern = {"abc",
                                   "abcd",
                                   "def",
                                   "aa",
                                   "aaab",
                                   "a",
                                   "abba",
                                   "b",
                                   "baab",
                                   "they",
                                   "c",
                                   "bbab",
                                   "are",
                                   "a",
                                   "c",
                                   "bbab",
                                   "are",
                                   "a",
                                   "abc",
                                   "abbaabbabbbab"};

std::vector<int> answers = { WRONG_LEN,
                             WRONG_LEN,
                             NOT_FOUND,
                             NOT_FOUND,
                             NOT_FOUND,
                             0,
                             0,
                             1,
                             2,
                             6,
                             2,
                             5,
                             11,
                             0,
                             2,
                             5,
                             11,
                             0,
                             0,
                             0 };





void tests()
{
    int count_success = 0;
    int kmp_ind, bm_ind;
    for(int i = 0; i < COUNT_TESTS; i++) {
        kmp_ind = kmp_search(text[i], pattern[i]);
        bm_ind = bm_search(text[i], pattern[i]);

        std::cout << "\ntext:  " << text[i] << std::endl;
        std::cout << "pattern:  " << pattern[i] << std::endl;
        std::cout << "kmp index: " << kmp_ind << " bm index: " << bm_ind << std::endl;

        if (kmp_ind == answers[i] && bm_ind == answers[i])
        {
            std::cout << "TEST OK" << std::endl;
            count_success++;
        }
        else {
            std::cout << "TEST FAILED" << std::endl;
        }

    }
    std::cout << "Tests success: " << count_success << "/" << COUNT_TESTS << std::endl;
}

