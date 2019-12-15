#ifndef EDGE
#define EDGE ___

#include "monitor.cpp"

class Edge
{
public:
    char u,v;
    int h;
    EdgeMonitor* monitor;
    Edge(char _u, char _v, int _h): u(_u), v(_v), h(_h) {
        monitor = new EdgeMonitor(_h);
    }
};

#endif