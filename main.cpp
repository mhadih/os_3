#include <vector>
#include <string>
#include <fstream>

using namespace std;

#define INPUT_PATH "in.txt"
#define OUTPUT_PATH "out.txt"

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

void read_input(ifstream file)
{
    string line;
    while(getline(file, line)) {
        if(line == "#")
            break;
        else {
            vector<string> words = split(line, '-');
            string new_edge = Edge(words[0][0], words[1][0], stoi(words[2]));
            edge_monitors[new_edge] = new EdgeMonitor(paths_h[new_edge]);
        }
    }
}

int main()
{
    ifstream file;
    file.open(INPUT_PATH);
    read_input(file);
}