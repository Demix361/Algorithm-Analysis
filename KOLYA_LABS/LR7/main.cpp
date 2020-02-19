#include <QCoreApplication>

#include "search_string.h"
#include "test.h"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    std::string s = "test";
    std::string t = "zestesctestpppp";
    std::vector<int> fail = create_state_machine(s);
    //for(int i = 0; i < fail.size(); i++)
    //    std::cout << fail[i];
    int res = k_m_p(t, s, fail);
    std::cout << "\n" << res << "\n";
    std::vector<int> sh= create_arr_shift(s);
    std::vector<int> jmp= create_arr_jump(s);
    res = b_m(t,s,sh,jmp);
    std::cout << "\n" << res << "\n";
    return 0;
}

//int main(int argc, char *argv[])
//{
//    test(std::string("test.txt"));
//    return 0;
//}
