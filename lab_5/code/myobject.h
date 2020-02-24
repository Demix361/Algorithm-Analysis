#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


class MyObject
{
public:
    MyObject(int id, int a);
    void setTime(int time);
    void printTimes();
    void timesToFile(ofstream &fout);
    void set_a(unsigned long int a) {this->a = a;}
    unsigned long int get_a() {return  this->a;}

private:
    unsigned long int a;
    int _id;
    vector<int> _times;
};

#endif // MYOBJECT_H
