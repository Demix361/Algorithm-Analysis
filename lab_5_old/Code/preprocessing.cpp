#include "preprocessing.h"

PreProcessing::PreProcessing(int count, QTime *timer, Processing *p, QMutex *mutex2)
{
    this->_count = count;
    this->_timer = timer;
    this->_proc = p;
    this->_mutex2 = mutex2;
}

void PreProcessing::addToQueue(MyObject obj)
{
    _queue.push(obj);
}

void PreProcessing::process()
{
    while (preprocessed != _count)
    {
        if (_queue.size() != 0)
        {
            // cout << "PreProcessing" << _timer->elapsed() << endl;
            MyObject obj = _queue.front();

            obj.setTime(_timer->elapsed());

            unsigned long fac = this->fac(obj.get_a());
            obj.set_a(fac);

            obj.setTime(_timer->elapsed());
            _queue.pop();
            _mutex2->lock();
            _proc->addToQueue(obj);
            _mutex2->unlock();
            preprocessed++;
        }
    }
}

unsigned long PreProcessing::fac(unsigned long int num)
{
    unsigned long int fac = 1;
    for (unsigned long int count = 1; count <= num; count++)
    {
        fac *= count;
    }

    return  fac;
}
