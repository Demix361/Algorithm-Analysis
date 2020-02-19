#pragma once

#include <iostream>
#include <vector>
#include <string>

#define WRONG_LEN -1
#define NOT_FOUND -2

std::vector<int> get_shift(const std::string &str);
int kmp(const std::string &text, const std::string &pattern);
int bm(const std::string &text, const std::string &pattern);
