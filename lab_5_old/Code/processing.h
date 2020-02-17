#ifndef PROCESSING_H
#define PROCESSING_H

#include <iostream>
#include <queue>
#include <QThread>
#include <QTime>
#include <QMutex>

#include "myobject.h"
#include "postprocessing.h"

using namespace std;
class Processing
{
public:
    Processing(int count, QTime *timer, PostProcessing *p, QMutex *mutex2, QMutex *mutex3);
    void addToQueue(MyObject obj);
    void process();
private:
    queue<MyObject> _queue;
    QTime *_timer;
    PostProcessing *_proc;
    QMutex *_mutex2;
    QMutex *_mutex3;
    int _count;
    int processed = 0;
    unsigned long int nod_pow(unsigned long int a, unsigned long int b);
};

#endif // PROCESSING_H
