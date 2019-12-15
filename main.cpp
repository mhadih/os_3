#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <chrono>

#include "path.cpp"
#include "edge.cpp"

using namespace std;

#define INPUT_PATH "in.txt"
#define OUTPUT_PATH "out.txt"

vector<Path*> paths;
map< pair<char, char>, Edge*> edge_objects;
EmmisionMonitor emmision_monitor; 

class ThreadArgs
{
public:
    Path* path;
    ThreadArgs(Path* p): path(p) { }
};

bool is_white_space(char ch)
{
    return (ch==' ' || ch=='\t');
}

vector<string> split(string line, char delimiter)
{
    vector<string> res;
    string cur_word = "";
    for (int i = 0; i<line.size(); i++)
    {
        if (is_white_space(line[i]))
            continue;
        if (line[i] == delimiter)
            res.push_back(cur_word);
        cur_word += line[i];
    }
    res.push_back(cur_word);
    return res;
}

vector<Edge*> create_edges(vector<string> path_edges_str)
{
    vector<Edge*> edges;
    for (int i = 0; i<path_edges_str.size()-1; i++)
    {
        char u = path_edges_str[i][0];
        char v = path_edges_str[i+1][0];
        edges.push_back(edge_objects[{u,v}]);
    }
    return edges;
}

void read_input(ifstream& file)
{
    string line;
    int edge_counter = 0;
    while(getline(file, line)) 
    {
        if(line == "#")
            break;
        else {
            vector<string> words = split(line, '-');
            char u = words[0][0];
            char v = words[1][0];
            int h = stoi(words[2]);
            Edge* new_edge = new Edge(u, v, h);
            edge_objects[{u,v}] = new_edge;
        }
    }
    int path_counter = 0;
    int car_counter = 0;
    while (getline(file, line))
    {
        vector<string> path_edges_str = split(line, '-');
        getline(file, line);
        int car_numbers = stoi(line);
        int path_id = path_counter++;
        for(int i = 0; i < car_numbers; i++) {
            paths.push_back(new Path(path_id, car_counter++, create_edges(path_edges_str)));
        }
    }
}

auto get_time()
{
    // return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now);
    return time(NULL);
}

void* thread_func(void* _args)
{
    ThreadArgs *args = (ThreadArgs*)_args;
    Path* path = args->path;

    ofstream file;
    string file_name = 
        "outputs/" +
        to_string(path->path_id) +
        "-" + to_string(path->car_id);
    file.open(file_name);

    int p = rand()%10 + 1;     
    for(Edge* edge: path->edges) 
    {
        char entrance_node_name = edge->u;
        char exit_node_name = edge->v;

        auto entrance_time = get_time();
        
        long double emmision = edge->monitor->run(p);
        emmision_monitor.add_emmision(emmision);
        long double total_emmision = emmision_monitor.get_total_emmision();

        auto exit_time123 = get_time();

        file << 
            entrance_node_name << ", " <<
            entrance_time << ", " << 
            exit_node_name << ", " << 
            exit_time123 << ", " << 
            emmision << ", " << 
            total_emmision << "\n";
    }
    file.close();
    pthread_exit(NULL);
}

int main()
{
    ifstream file;
    file.open(INPUT_PATH);
    read_input(file);
    int cars_num = paths.size();

    pthread_t threads[cars_num];
    for(int i = 0; i < cars_num; i++) {
        ThreadArgs* args = new ThreadArgs(paths[i]);
        int ret = pthread_create(&threads[i], NULL, thread_func, args);
        if(ret != 0) {
                perror("pthread_create failed\n");
                exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < cars_num; i++) {
        pthread_join(threads[i], NULL);
    }
}