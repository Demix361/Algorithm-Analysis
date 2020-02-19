#include "search_string.h"
#include <QDebug>
#include <iostream>

int k_m_p(std::string text, std::string sub)
{
    return k_m_p(text, sub, create_state_machine(sub));
}

int b_m(std::string text, std::string sub)
{
    return b_m(text, sub, create_arr_shift(sub), create_arr_jump(sub));
}

int k_m_p(std::string text, std::string sub, std::vector<int> fail)
{
    int subloc = 1, textloc = 1;
    int res = -1;
    while ((subloc <= (int)sub.size()) && (textloc <= (int)text.size()))
    {
        if((subloc == 0) || (text[textloc - 1] == sub[subloc - 1]))
        {
            textloc++;
            subloc++;
        }
        else
            subloc = fail[subloc - 1];
    }
    if(subloc > sub.size())
        res = textloc - sub.size() - 1;
    return res;
}

std::vector<int> create_state_machine(std::string s)
{
    std::vector<int> fail;
    for(unsigned int i = 0; i < s.size();i++)
        fail.push_back(0);
    for(unsigned int i = 1; i < s.size();i++)
    {
        int tmp = fail[i - 1];
        while((tmp > 0) && (s[tmp - 1] != s[i - 1]))
            tmp = fail[tmp - 1];
        fail[i] = tmp + 1;
    }
    return fail;
}

std::vector<int> create_arr_shift(std::string sub)
{
    std::vector<int> shift;
    for(int i = 0; i < ALPH_SIZE; i++)
        shift.push_back(sub.size());
    for(int i = 0; i <  sub.size(); i++)
    {
        shift[(int) sub[i]] = i - 1;
    }
    return shift;
}

std::vector<int> create_arr_jump(std::string sub)
{
    std::vector<int> jump, link;
    for(int i = 0; i < sub.size(); i++)
    {
        jump.push_back(2*sub.size() - i - 1);
        link.push_back(0);
    }
    link.push_back(0);
    int test = sub.size() - 1;
    int target = sub.size();
    while(test > 0)
    {
        link[test] = target;
        while ((target < sub.size()) && (sub[test] != sub[target]))
        {
            jump[target] = std::min(jump[target], (int)sub.size() - test - 1);
            target = link[target];
        }
        test--;
        target--;
    }
    for(int i = 0; i < target; i++)
        jump[i] = std::min(jump[i], (int)sub.size() + target - i - 1);
    int tmp = link[target];
    while(target < sub.size())
    {
        while(target < tmp)
        {
            jump[target] = std::min(jump[target], tmp - target + (int)sub.size() + 1);
            target++;
        }
        tmp = link[tmp];
    }
    return jump;
}

int b_m(std::string text, std::string sub , std::vector<int> shift, std::vector<int> jump)
{
    int res = -1;
    int textLoc = sub.size() - 1;
    int subLoc = sub.size() - 1;
    while ((textLoc <= text.size()) && (subLoc >= 0))
    {
        if (text[ textLoc ] == sub[ subLoc ])
        {
            textLoc--;
            subLoc--;
        }
        else
        {
            std::cout <<shift[(int)text[textLoc]] << " " <<jump[subLoc]<< "\n";
            textLoc = textLoc + std::max(shift[(int)text[textLoc]], jump[subLoc]);
             subLoc = sub.size() - 1;
        }

    }
    if (subLoc == -1)
        res = textLoc + 1;
    return res;
}
