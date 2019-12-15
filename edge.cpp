
class Edge
{
public:
    char u,v;
    int h;
    Monitor* monitor;
    Edge(char _u, char _v, int _h): u(_u), v(_v), h(_h) {
        monitor = new Monitor(paths_h[new_edge]);
    }
};