#include "processing.h"


Processing::Processing(int count, QTime *timer, PostProcessing *p, QMutex *mutex2, QMutex *mutex3)
{
    this->_count = count;
    this->_timer = timer;
    this->_proc = p;
    this->_mutex2 = mutex2;
    this->_mutex3 = mutex3;
}


void Processing::addToQueue(MyObject obj)
{
    _queue.push(obj);
}


void Processing::process()
{
    while (processed != _count)
    {
        if (_queue.size() != 0)
        {
            // cout << "Processing" << _timer->elapsed() << endl;
            MyObject obj = _queue.front();
            QThread thread;
            obj.setTime(_timer->elapsed());

            unsigned long nod = this->nod_pow(obj.get_a(), 11);
            obj.set_a(nod);

            obj.setTime(_timer->elapsed());

            _mutex2->lock();
            _queue.pop();
            _mutex2->unlock();

            _mutex3->lock();
            _proc->addToQueue(obj);
            _mutex3->unlock();

            processed++;
        }
    }
}


unsigned long Processing::nod_pow(unsigned long a, unsigned long b)
{
    unsigned long int nod = 0;

    for (unsigned long int i = a; i > 0; i--)
    {
        if (a % i == 0 && b % i == 0)
        {
            nod = i;
            break;
        }
    }

    unsigned long result = 1;

    for (int i = 0; i < 10000000; i++)
        result *= nod;


    return result;
}
