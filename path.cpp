#ifndef PATH
#define PATH ___

#include <vector>

#include "edge.cpp"

using namespace std;

class Path
{
public:
    int path_id;
    int car_id;
    vector<Edge*> edges;
    Path(int p, int id, vector<Edge*> e): path_id(p), car_id(id), edges(e) { }
};

#endif