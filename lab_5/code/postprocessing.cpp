#include "postprocessing.h"

PostProcessing::PostProcessing(int count, QTime *timer, vector<MyObject> *dump, QMutex *mutex3)
{
    this->_count = count;
    this->_timer = timer;
    this->_dump = dump;
    this->_mutex3 = mutex3;
}

void PostProcessing::addToQueue(MyObject obj)
{
    _queue.push(obj);
}

void PostProcessing::process()
{
    while (postprocessed != _count)
    {
        if (_queue.size() != 0)
        {
            // cout << "PostProcessing" << _timer->elapsed() << endl;
            MyObject obj = _queue.front();
            QThread thread;
            obj.setTime(_timer->elapsed());

            unsigned long int power = this->power(obj.get_a(), 10000000);
            obj.set_a(power);

            obj.setTime(_timer->elapsed());

            _mutex3->lock();
            _queue.pop();
            _mutex3->unlock();

            _dump->push_back(obj);
            postprocessed++;
        }
    }
}

unsigned long PostProcessing::power(unsigned long a, unsigned long b)
{
    unsigned long int res = 1;

    for (unsigned long int i = 0; i < b; i++)
    {
        res *= a;
    }

    return  res;
}
