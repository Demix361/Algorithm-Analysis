#ifndef SEARCH_STRING_H
#define SEARCH_STRING_H

#define ALPH_SIZE 256

#include <string>
#include <vector>
std::vector<int> create_state_machine(std::string s);
int k_m_p(std::string text, std::string sub, std::vector<int> fail);
int k_m_p(std::string text, std::string sub);
std::vector<int> create_arr_shift(std::string sub);
std::vector<int> create_arr_jump(std::string sub);
int b_m(std::string text, std::string sub , std::vector<int> shift, std::vector<int> jump);
int b_m(std::string text, std::string sub);
#endif // SEARCH_STRING_H
