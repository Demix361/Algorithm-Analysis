#include <QCoreApplication>
#include <QTime>
#include <QMutex>
#include <cstdlib>

#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <fstream>

#include "myobject.h"
#include "preprocessing.h"
#include "processing.h"
#include "postprocessing.h"


using namespace std;
const int MIN_RAND =  10;
const int MAX_RAND =  15;
const int COUNT = 40;

const string LOG_FILE_3_TH = "log_3_th.txt";
const string LOG_FILE_NO_TH = "log_no_th.txt";

void consistent(MyObject **objs);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    srand(static_cast<unsigned int>(time(nullptr)));

    MyObject *objs[COUNT];

    for (int i = 0; i < COUNT; ++i)
    {
        int myrand = rand() % MAX_RAND + MIN_RAND;

        objs[i] = new MyObject(i, myrand);
    }

    consistent(objs);

    QTime timer;
    timer.restart();

    int start_time = timer.elapsed();

    vector<MyObject> dump;

    QMutex *mutex2 = new QMutex;
    QMutex *mutex3 = new QMutex;

    PostProcessing *postproc = new PostProcessing(COUNT, &timer, &dump, mutex2);
    Processing *proc = new Processing(COUNT, &timer, postproc, mutex2, mutex3);
    PreProcessing *preproc = new PreProcessing(COUNT, &timer, proc, mutex3);

    for (int i = 0; i < COUNT; ++i)
    {
        preproc->addToQueue(*objs[i]);
    }

    vector<thread> threads;
    threads.push_back(thread(&PreProcessing::process, preproc));
    threads.push_back(thread(&Processing::process, proc));
    threads.push_back(thread(&PostProcessing::process, postproc));

    for (unsigned int i = 0; i <  threads.size(); ++i)
    {
        if (threads.at(i).joinable())
            threads.at(i).join();
    }

    int total_time = timer.elapsed() - start_time;

    ofstream fout(LOG_FILE_3_TH);
    if (fout.is_open())
    {
        for (unsigned int i = 0; i < dump.size(); ++i)
            dump.at(i).timesToFile(fout);
        fout << "Total time: " << total_time << endl;
        cout << "Results in: " << LOG_FILE_3_TH << endl;
    }
    else
        cout << "I cant open file " << LOG_FILE_3_TH << endl;
    fout.close();


    delete mutex2;
    delete mutex3;
    delete preproc;
    delete proc;
    delete postproc;

    return 0;
}

void consistent(MyObject **objs)
{
    QTime timer;
    timer.restart();

    int start_time = timer.elapsed();

    vector<MyObject> dump;

    QMutex *mutex2 = new QMutex;
    QMutex *mutex3 = new QMutex;

    PostProcessing *postproc = new PostProcessing(COUNT, &timer, &dump, mutex2);
    Processing *proc = new Processing(COUNT, &timer, postproc, mutex2, mutex3);
    PreProcessing *preproc = new PreProcessing(COUNT, &timer, proc, mutex3);

    for (int i = 0; i < COUNT; ++i)
    {
        preproc->addToQueue(*objs[i]);
    }

    preproc->process();
    proc->process();
    postproc->process();

    int total_time = timer.elapsed() - start_time;

    ofstream fout(LOG_FILE_NO_TH);
    if (fout.is_open())
    {
        for (unsigned int i = 0; i < dump.size(); ++i)
            dump.at(i).timesToFile(fout);
        fout << "Total time: " << total_time << endl;
        cout << "Results in: " << LOG_FILE_NO_TH << endl;
    }
    else
        cout << "I cant open file " << LOG_FILE_NO_TH << endl;
    fout.close();


    delete mutex2;
    delete mutex3;
    delete preproc;
    delete proc;
    delete postproc;
}
