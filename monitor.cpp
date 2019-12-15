#ifndef MONITOR
#define MONITOR

#include <thread>
#include <semaphore.h>

class EdgeMonitor
{
private:
    sem_t mutex;
    int h;
public:
    EdgeMonitor(int _h)
    {
        sem_init(&mutex, 0, 1);
        h = _h;
    }
    float run(int p)
    {
        sem_wait(&mutex);
        float res;
        for(int k = 0; k < 3 * 1e8; k++) 
            res += k/(p*h*1e6);
        sem_post(&mutex);
        return res;
    }
};

class EmmisionMonitor
{
private:
    sem_t mutex;
    float total_emmision;
public:
    EmmisionMonitor()
    {
        total_emmision = 0;
        sem_init(&mutex, 0, 1);
    }
    void add_emmision(float emmision)
    {
        sem_wait(&mutex);
        total_emmision += emmision;
        sem_post(&mutex);
    }
    float get_total_emmision()
    {
        return total_emmision;
    }
};

#endif