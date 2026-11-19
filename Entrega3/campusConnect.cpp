#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Edge{
    int u;
    int value;
    int cost;
    bool failure = false;
};

struct Node{
    int id;
    string name;
    string ip;
};