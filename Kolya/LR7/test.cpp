#include "test.h"

int test(std::string filename)
{
    std::ifstream f(filename);
    if (!f.is_open())
        return 0;
    while(!f.eof())
    {
        std::string s, t;
        f >> t >> s;
        int r1, r2, r3;
        std::vector<int> fail = create_state_machine(s);
        std::vector<int> sh= create_arr_shift(s);
        std::vector<int> jmp= create_arr_jump(s);
        r1 = k_m_p(t, s, fail);
        r2 = b_m(t, s, sh, jmp);
        r3 = t.find(s);
        std::cout << s <<" " << t << " " << r1 << " " << r2 << " " << r3 << "\n";
    }
}
