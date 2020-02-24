#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include <iostream>
#include <QThread>
#include <QTime>
#include <QMutex>

#include <queue>
#include <vector>

#include "myobject.h"

class PostProcessing
{
public:
    PostProcessing(int count, QTime *timer, vector<MyObject> *dump, QMutex *mutex3);
    void addToQueue(MyObject obj);
    void process();
private:
    queue<MyObject> _queue;
    QTime *_timer;
    vector<MyObject> *_dump;
    QMutex *_mutex3;
    int _count;
    int postprocessed = 0;
    unsigned long int power(unsigned long int a, unsigned long int b);
};

#endif // POSTPROCESSING_H
