#pragma once

class Key
{
public:
    Key() : e(e_), n(n_)  { }
    ~Key() { }
    void set(int e_, int n_) {

    }
    int get_e() { return e; }
    int get_n() { return n; }
private:
    int e, n;
};
