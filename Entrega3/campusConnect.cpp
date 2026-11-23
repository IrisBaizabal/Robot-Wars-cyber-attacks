// This program implements CAMPUS CONNECT!, a university network planning system
// that builds minimum-cost networks, finds communication routes, handles cable
// failures and campus expansion, and exports visual network graphs using Graphviz.
// Authors: Carmen Iris Vasquez Baizabal - A00843705, Francisco Santos Martinez Ortiz - A00843605, Erika Esquivel Correa A00841206
// Date: 11/22/2026

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class Stack {
private:
    vector<int> data;

public:
    // Initializes an empty stack
    // O(1)
    Stack() {
    }

    // Inserts an element at the top of the stack
    // O(1)
    void push(int value) {
        data.push_back(value);
    }

    // Removes and returns the top element of the stack
    // O(1)
    int pop() {
        int value = -1;
        if (!isEmpty()) {
            value = data.back();
            data.pop_back();
        }
        return value;
    }

    // Checks if the stack is empty
    // O(1)
    bool isEmpty() {
        return data.empty();
    }
};

class Queue {
private:
    vector<int> data;
    int frontIndex;

public:
    // Initializes an empty queue
    // O(1)
    Queue() {
        frontIndex = 0;
    }

    // Inserts an element at the end of the queue
    // O(1)
    void enqueue(int value) {
        data.push_back(value);
    }

    // Removes and returns the front element of the queue
    // O(1)
    int dequeue() {
        int value = -1;
        if (!isEmpty()) {
            value = data[frontIndex];
            frontIndex++;
        }
        return value;
    }

    // Checks if the queue is empty
    // O(1)
    bool isEmpty() {
        return frontIndex >= (int)data.size();
    }
};

class Node {
public:
    char id;
    int x;
    int y;

    // Initializes a default building node
    // O(1)
    Node() {
        id = ' ';
        x = 0;
        y = 0;
    }

    // Initializes a building node with its character ID and coordinates
    // O(1)
    Node(char nodeId, int posX, int posY) {
        id = nodeId;
        x = posX;
        y = posY;
    }
};

class Edge {
public:
    char from;
    char to;
    int weight;

    // Initializes a default edge
    // O(1)
    Edge() {
        from = ' ';
        to = ' ';
        weight = 0;
    }

    // Initializes an edge between two buildings with a weight
    // O(1)
    Edge(char nodeFrom, char nodeTo, int edgeWeight) {
        from = nodeFrom;
        to = nodeTo;
        weight = edgeWeight;
    }
};

class Graph {
private:
    vector<Node> nodes;
    vector<vector<int>> matrix;
    int n;
    int e;

public:
    // Initializes an empty graph
    // O(1)
    Graph() {
        n = 0;
        e = 0;
    }

    // Searches for the matrix index corresponding to a building ID
    // O(V)
    int findNodeIndex(char id) {
        int index = -1;
        int i = 0;
        while (i < n && index == -1) {
            if (nodes[i].id == id) {
                index = i;
            }
            i++;
        }
        return index;
    }

    // Registers a new building and expands the adjacency matrix
    // O(V)
    void addNode(char id, int x, int y) {
        if (findNodeIndex(id) == -1) {
            nodes.push_back(Node(id, x, y));
            n = (int)nodes.size();

            for (int i = 0; i < n - 1; i++) {
                matrix[i].push_back(0);
            }

            vector<int> newRow(n, 0);
            matrix.push_back(newRow);
        }
    }

    // Connects two buildings by index with a given installation cost
    // O(1)
    void addEdge(int a, int b, int weight = 1) {
        if (a >= 0 && a < n && b >= 0 && b < n && a != b) {
            if (matrix[a][b] == 0) {
                e++;
            }
            matrix[a][b] = weight;
            matrix[b][a] = weight;
        }
    }

    // Connects two buildings using their character identifiers
    // O(V)
    void addEdgeByChar(char u, char v, int weight) {
        int a = findNodeIndex(u);
        int b = findNodeIndex(v);
        if (a != -1 && b != -1) {
            addEdge(a, b, weight);
        }
    }

    // Removes an existing connection between two building indices
    // O(1)
    void removeEdge(int a, int b) {
        if (a >= 0 && a < n && b >= 0 && b < n) {
            if (matrix[a][b] != 0) {
                matrix[a][b] = 0;
                matrix[b][a] = 0;
                e--;
            }
        }
    }

    // Removes a connection using building character identifiers
    // O(V)
    void removeEdgeByChar(char u, char v) {
        int a = findNodeIndex(u);
        int b = findNodeIndex(v);
        if (a != -1 && b != -1) {
            removeEdge(a, b);
        }
    }

    // Returns the weight of an edge given indices
    // O(1)
    int getEdgeWeightByIndex(int a, int b) {
        int weight = 0;
        if (a >= 0 && a < n && b >= 0 && b < n) {
            weight = matrix[a][b];
        }
        return weight;
    }

    // Returns the weight of an edge given character identifiers
    // O(V)
    int getEdgeWeightByChar(char u, char v) {
        int a = findNodeIndex(u);
        int b = findNodeIndex(v);
        int weight = 0;
        if (a != -1 && b != -1) {
            weight = matrix[a][b];
        }
        return weight;
    }

    // Returns the total count of registered buildings
    // O(1)
    int getNodeCount() {
        return n;
    }

    // Returns the building identifier at a given matrix index
    // O(1)
    char getNodeId(int index) {
        char id = ' ';
        if (index >= 0 && index < n) {
            id = nodes[index].id;
        }
        return id;
    }

    // Returns the X coordinate of a building at a given index
    // O(1)
    int getNodeX(int index) {
        int x = 0;
        if (index >= 0 && index < n) {
            x = nodes[index].x;
        }
        return x;
    }

    // Returns the Y coordinate of a building at a given index
    // O(1)
    int getNodeY(int index) {
        int y = 0;
        if (index >= 0 && index < n) {
            y = nodes[index].y;
        }
        return y;
    }

    // Calculates the total sum of installation costs of all installed connections
    // O(V^2)
    int getTotalCost() {
        int total = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                total += matrix[i][j];
            }
        }
        return total;
    }

    // Copies only the building nodes to another graph and resets all edges
    // O(V^2)
    void copyNodesFrom(Graph& other) {
        nodes = other.nodes;
        n = other.n;
        e = 0;
        matrix.assign(n, vector<int>(n, 0));
    }

    // Copies the full graph topology from another graph
    // O(V^2)
    void copyFrom(Graph& other) {
        nodes = other.nodes;
        matrix = other.matrix;
        n = other.n;
        e = other.e;
    }

    // Prints installed edges and costs in a concise single-line format
    // O(V^2)
    void printCompactEdges() {
        int count = 0;
        cout << "   ";
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (matrix[i][j] != 0) {
                    cout << "(" << nodes[i].id << "-" << nodes[j].id << ":" << matrix[i][j] << ") ";
                    count++;
                }
            }
        }
        if (count == 0) {
            cout << "None";
        }
        cout << endl;
    }

    // Checks whether the network is fully connected using BFS
    // O(V^2)
    bool isConnected() {
        if (n == 0) {
            return true;
        }

        vector<bool> visited(n, false);
        Queue q;

        q.enqueue(0);
        visited[0] = true;
        int count = 1;

        while (!q.isEmpty()) {
            int curr = q.dequeue();
            for (int j = 0; j < n; j++) {
                if (matrix[curr][j] != 0 && !visited[j]) {
                    visited[j] = true;
                    q.enqueue(j);
                    count++;
                }
            }
        }

        return count == n;
    }

    // Displays the connected components of the campus network
    // O(V^2)
    void printComponents() {
        vector<bool> visited(n, false);
        int groupNumber = 1;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                Queue q;
                q.enqueue(i);
                visited[i] = true;
                cout << "   Group " << groupNumber << ": ";

                while (!q.isEmpty()) {
                    int curr = q.dequeue();
                    cout << nodes[curr].id << " ";
                    for (int j = 0; j < n; j++) {
                        if (matrix[curr][j] != 0 && !visited[j]) {
                            visited[j] = true;
                            q.enqueue(j);
                        }
                    }
                }
                cout << endl;
                groupNumber++;
            }
        }
    }

    // Builds the Minimum Spanning Tree using Prim's algorithm
    // O(V^2)
    bool buildMST(Graph& mstGraph) {
        mstGraph.copyNodesFrom(*this);
        if (n == 0) {
            return true;
        }

        vector<int> distance(n, 999999);
        vector<int> processed(n, 0);
        vector<int> from(n, -1);

        distance[0] = 0;

        for (int i = 0; i < n; i++) {
            int u = -1;
            int minDist = 999999;

            for (int j = 0; j < n; j++) {
                if (processed[j] == 0 && distance[j] < minDist) {
                    minDist = distance[j];
                    u = j;
                }
            }

            // Handles disconnected components cleanly if some buildings are unreachable
            if (u == -1) {
                int j = 0;
                while (j < n && u == -1) {
                    if (processed[j] == 0) {
                        u = j;
                        distance[u] = 0;
                    }
                    j++;
                }
            }

            if (u != -1) {
                processed[u] = 1;
                for (int j = 0; j < n; j++) {
                    if (matrix[u][j] != 0 && processed[j] == 0) {
                        int newDist = matrix[u][j];
                        if (newDist < distance[j]) {
                            distance[j] = newDist;
                            from[j] = u;
                        }
                    }
                }
            }
        }

        int edgesAdded = 0;
        for (int i = 0; i < n; i++) {
            if (from[i] != -1) {
                mstGraph.addEdge(from[i], i, distance[i]);
                edgesAdded++;
            }
        }

        return edgesAdded == n - 1;
    }

    // Calculates the shortest communication route between two buildings using Dijkstra
    // O(V^2)
    vector<char> shortestPath(char startId, char endId) {
        vector<char> route;
        int start = findNodeIndex(startId);
        int end = findNodeIndex(endId);

        if (start == -1 || end == -1) {
            cout << "Route " << startId << " -> " << endId << ": Invalid building ID" << endl;
            return route;
        }

        vector<int> distance(n, 999999);
        vector<int> processed(n, 0);
        vector<int> from(n, -1);

        distance[start] = 0;

        for (int i = 0; i < n; i++) {
            int u = -1;
            int minDist = 999999;

            for (int j = 0; j < n; j++) {
                if (processed[j] == 0 && distance[j] < minDist) {
                    minDist = distance[j];
                    u = j;
                }
            }

            if (u != -1) {
                processed[u] = 1;
                for (int j = 0; j < n; j++) {
                    if (matrix[u][j] != 0 && processed[j] == 0) {
                        int newDist = distance[u] + matrix[u][j];
                        if (newDist < distance[j]) {
                            distance[j] = newDist;
                            from[j] = u;
                        }
                    }
                }
            }
        }

        cout << "Route " << startId << " -> " << endId << ": ";
        if (distance[end] == 999999) {
            cout << "Unreachable" << endl;
        } else {
            Stack pathStack;
            int curr = end;
            while (curr != -1) {
                pathStack.push(curr);
                curr = from[curr];
            }

            while (!pathStack.isEmpty()) {
                char nodeId = nodes[pathStack.pop()].id;
                route.push_back(nodeId);
                cout << nodeId;
                if (!pathStack.isEmpty()) {
                    cout << " -> ";
                }
            }
            cout << " | Cost: " << distance[end] << endl;
        }

        return route;
    }
};

// Adds the campus configuration with a file into the graph
// O(V+E)
bool loadCampusFile(string filename, Graph& availableGraph, vector<Edge>& failedEdges,
                    vector<Node>& newNodes, vector<Edge>& newEdges) {
    ifstream readFile(filename);
    if (!readFile.is_open()) {
        return false;
    }

    string line = "";
    string section = "";
    int declaredNodes = 0;
    int declaredEdges = 0;

    while (getline(readFile, line)) {
        stringstream ss(line);
        string token = "";

        if (ss >> token) {
            if (token[0] == '#') {
                string word1 = "";
                string word2 = "";

                if (token.size() > 1) {
                    word1 = token.substr(1);
                } else {
                    ss >> word1;
                }

                if (word1 == "NODES") {
                    section = "NODES";
                } else if (word1 == "EDGES") {
                    section = "EDGES";
                } else if (word1 == "FAILED") {
                    section = "FAILED";
                } else if (word1 == "NEW") {
                    ss >> word2;
                    if (word2 == "NODE" || word2 == "NODES") {
                        section = "NEW_NODE";
                    } else if (word2 == "EDGE" || word2 == "EDGES") {
                        section = "NEW_EDGES";
                    }
                }
            } else {
                stringstream data(line);

                if (section == "") {
                    data >> declaredNodes >> declaredEdges;
                } else if (section == "NODES") {
                    string idStr = "";
                    int x = 0;
                    int y = 0;
                    if (data >> idStr >> x >> y) {
                        availableGraph.addNode(idStr[0], x, y);
                    }
                } else if (section == "EDGES") {
                    string uStr = "";
                    string vStr = "";
                    int w = 0;
                    if (data >> uStr >> vStr >> w) {
                        availableGraph.addEdgeByChar(uStr[0], vStr[0], w);
                    }
                } else if (section == "FAILED") {
                    string uStr = "";
                    string vStr = "";
                    if (data >> uStr >> vStr) {
                        failedEdges.push_back(Edge(uStr[0], vStr[0], 0));
                    }
                } else if (section == "NEW_NODE") {
                    string idStr = "";
                    int x = 0;
                    int y = 0;
                    if (data >> idStr >> x >> y) {
                        newNodes.push_back(Node(idStr[0], x, y));
                    }
                } else if (section == "NEW_EDGES") {
                    string uStr = "";
                    string vStr = "";
                    int w = 0;
                    if (data >> uStr >> vStr >> w) {
                        newEdges.push_back(Edge(uStr[0], vStr[0], w));
                    }
                }
            }
        }
    }

    readFile.close();
    return true;
}

// Compares two network configurations by printing costs, and cables adding/removals
// O(V^2)
void compareNetworks(Graph& prevNet, Graph& currNet, string label) {
    int prevCost = prevNet.getTotalCost();
    int currCost = currNet.getTotalCost();
    int diff = currCost - prevCost;

    cout << "   " << label << ": " << prevCost << " -> " << currCost << " (";
    if (diff > 0) {
        cout << "+" << diff;
    } else {
        cout << diff;
    }
    cout << ") | Removed: ";

    int prevN = prevNet.getNodeCount();
    int remCount = 0;
    for (int i = 0; i < prevN; i++) {
        for (int j = i + 1; j < prevN; j++) {
            int w = prevNet.getEdgeWeightByIndex(i, j);
            if (w != 0) {
                char u = prevNet.getNodeId(i);
                char v = prevNet.getNodeId(j);
                if (currNet.getEdgeWeightByChar(u, v) == 0) {
                    cout << "(" << u << "-" << v << ":" << w << ") ";
                    remCount++;
                }
            }
        }
    }
    if (remCount == 0) {
        cout << "None ";
    }

    cout << "| Added: ";
    int currN = currNet.getNodeCount();
    int addCount = 0;
    for (int i = 0; i < currN; i++) {
        for (int j = i + 1; j < currN; j++) {
            int w = currNet.getEdgeWeightByIndex(i, j);
            if (w != 0) {
                char u = currNet.getNodeId(i);
                char v = currNet.getNodeId(j);
                if (prevNet.getEdgeWeightByChar(u, v) == 0) {
                    cout << "(" << u << "-" << v << ":" << w << ") ";
                    addCount++;
                }
            }
        }
    }
    if (addCount == 0) {
        cout << "None";
    }
    cout << endl;
}

// Generates the graphviz dot script and renders a png diagram
// O(V^2)
bool exportVisual(string baseName, string title, Graph& netGraph, Graph& contextGraph,
                  bool showContext, vector<Edge>& failedList, bool showFailed,
                  vector<char>& routePath, vector<Node>& newBuildings) {
    string dotFile = baseName + ".dot";
    string pngFile = baseName + ".png";
    ofstream outFile(dotFile);

    if (!outFile.is_open()) {
        return false;
    }

    outFile << "graph Campus {\n";
    outFile << "  label=\"" << title << "\";\n";
    outFile << "  labelloc=\"t\";\n";
    outFile << "  fontsize=16;\n";
    outFile << "  node [shape=circle, style=filled, width=0.6, fixedsize=true];\n";

    int n = netGraph.getNodeCount();
    for (int i = 0; i < n; i++) {
        char id = netGraph.getNodeId(i);
        int x = netGraph.getNodeX(i);
        int y = netGraph.getNodeY(i);

        string fillColor = "lightblue";
        int k = 0;
        while (k < (int)newBuildings.size()) {
            if (newBuildings[k].id == id) {
                fillColor = "lightgreen";
            }
            k++;
        }

        outFile << "  " << id << " [label=\"" << id << "\\n(" << x << "," << y
                << ")\", pos=\"" << x << "," << y << "!\", fillcolor=" << fillColor << "];\n";
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            char u = netGraph.getNodeId(i);
            char v = netGraph.getNodeId(j);
            int installedW = netGraph.getEdgeWeightByIndex(i, j);

            // Checks if this connection is in the failed cables list
            bool isFailed = false;
            if (showFailed) {
                int f = 0;
                while (f < (int)failedList.size() && !isFailed) {
                    if ((failedList[f].from == u && failedList[f].to == v) ||
                        (failedList[f].from == v && failedList[f].to == u)) {
                        isFailed = true;
                    }
                    f++;
                }
            }

            // Checks if this connection belongs to the queried Dijkstra communication route
            bool isInRoute = false;
            int r = 0;
            while (r + 1 < (int)routePath.size() && !isInRoute) {
                if ((routePath[r] == u && routePath[r + 1] == v) ||
                    (routePath[r] == v && routePath[r + 1] == u)) {
                    isInRoute = true;
                }
                r++;
            }

            if (isFailed) {
                outFile << "  " << u << " -- " << v
                        << " [label=\"X\", color=red, fontcolor=red, style=dotted, penwidth=2.0];\n";
            } else if (installedW != 0) {
                if (isInRoute) {
                    outFile << "  " << u << " -- " << v << " [label=\"" << installedW
                            << "\", color=darkgreen, fontcolor=darkgreen, penwidth=3.5];\n";
                } else {
                    outFile << "  " << u << " -- " << v << " [label=\"" << installedW
                            << "\", color=blue, fontcolor=blue, penwidth=2.5];\n";
                }
            } else if (showContext) {
                int availW = contextGraph.getEdgeWeightByChar(u, v);
                if (availW != 0) {
                    outFile << "  " << u << " -- " << v << " [label=\"" << availW
                            << "\", color=gray70, fontcolor=gray50, style=dashed];\n";
                }
            }
        }
    }

    outFile << "}\n";
    outFile.close();

    // Invokes Graphviz neato engine to render coordinates to an image
    string command = "neato -Tpng " + dotFile + " -o " + pngFile;
    int res = system(command.c_str());
    return (res == 0);
}

// Executes the complete CAMPUS CONNECT! simulation across all evaluation phases
// O(V^2)
void runCampusConnect(string filename, char routeStart, char routeEnd) {
    Graph availableGraph;
    vector<Edge> failedEdges;
    vector<Node> newNodes;
    vector<Edge> newEdges;

    if (!loadCampusFile(filename, availableGraph, failedEdges, newNodes, newEdges)) {
        cout << "Could not open file: " << filename << endl;
        return;
    }

    vector<char> emptyRoute;
    vector<Node> emptyNewNodes;
    bool imagesOk = true;

    // 1. Available campus network visual
    imagesOk = exportVisual("1_available", "1. Available Campus Cables", availableGraph, availableGraph, false, failedEdges, false, emptyRoute, emptyNewNodes) && imagesOk;

    // 2. Original MST
    Graph originalNetwork;
    bool origOk = availableGraph.buildMST(originalNetwork);
    cout << "Original MST | Cost: " << originalNetwork.getTotalCost() << (origOk ? "" : " (Incomplete)") << endl;
    originalNetwork.printCompactEdges();
    if (!origOk) {
        originalNetwork.printComponents();
    }
    imagesOk = exportVisual("2_original_mst", "2. Original MST (Cost: " + to_string(originalNetwork.getTotalCost()) + ")", originalNetwork, availableGraph, true, failedEdges, false, emptyRoute, emptyNewNodes) && imagesOk;

    // 3. Shortest communication route
    vector<char> route = originalNetwork.shortestPath(routeStart, routeEnd);
    imagesOk = exportVisual("3_route", string("3. Route ") + routeStart + " to " + routeEnd, originalNetwork, availableGraph, false, failedEdges, false, route, emptyNewNodes) && imagesOk;

    // 4. Connection failure
    Graph failedNetwork;
    failedNetwork.copyFrom(originalNetwork);
    for (int i = 0; i < (int)failedEdges.size(); i++) {
        availableGraph.removeEdgeByChar(failedEdges[i].from, failedEdges[i].to);
        failedNetwork.removeEdgeByChar(failedEdges[i].from, failedEdges[i].to);
    }
    bool afterFailConnected = failedNetwork.isConnected();
    cout << "Failure | Connected: " << (afterFailConnected ? "Yes" : "No") << endl;
    if (!afterFailConnected) {
        failedNetwork.printComponents();
    }
    imagesOk = exportVisual("4_failure", "4. Network After Cable Failure", failedNetwork,availableGraph, false, failedEdges, true, emptyRoute, emptyNewNodes) && imagesOk;

    // 5. Restored network
    Graph restoredNetwork;
    bool restoredOk = availableGraph.buildMST(restoredNetwork);
    cout << "Restored MST | Cost: " << restoredNetwork.getTotalCost()
         << (restoredOk ? "" : " (Restoration impossible)") << endl;
    restoredNetwork.printCompactEdges();
    if (!restoredOk) {
        restoredNetwork.printComponents();
    }
    imagesOk = exportVisual("5_restored_mst", "5. Restored MST (Cost: " + to_string(restoredNetwork.getTotalCost()) + ")", restoredNetwork, availableGraph, true, failedEdges, true, emptyRoute, emptyNewNodes) && imagesOk;

    // 6. Campus expansion
    for (int i = 0; i < (int)newNodes.size(); i++) {
        availableGraph.addNode(newNodes[i].id, newNodes[i].x, newNodes[i].y);
    }
    for (int i = 0; i < (int)newEdges.size(); i++) {
        availableGraph.addEdgeByChar(newEdges[i].from, newEdges[i].to, newEdges[i].weight);
    }

    Graph expandedNetwork;
    bool expandedOk = availableGraph.buildMST(expandedNetwork);
    cout << "Expanded MST | Cost: " << expandedNetwork.getTotalCost()
         << (expandedOk ? "" : " (Incomplete)") << endl;
    expandedNetwork.printCompactEdges();
    if (!expandedOk) {
        expandedNetwork.printComponents();
    }
    imagesOk = exportVisual("6_expanded_mst","6. Expanded MST (Cost: " + to_string(expandedNetwork.getTotalCost()) + ")",expandedNetwork, availableGraph, true, failedEdges, true, emptyRoute, newNodes) && imagesOk;

    // 7. Topology comparison
    cout << "Comparison:" << endl;
    compareNetworks(originalNetwork, restoredNetwork, "Orig -> Rest");
    compareNetworks(restoredNetwork, expandedNetwork, "Rest -> Exp ");
    compareNetworks(originalNetwork, expandedNetwork, "Orig -> Exp ");

    if (imagesOk) {
        cout << "Images created" << endl;
    } else {
        cout << "DOT files created" << endl;
    }
    cout << endl;
}

int main() {
     string filename = "test_fix3.txt";
    char startBuilding = 'A';
    char endBuilding = 'F';

    runCampusConnect(filename, startBuilding, endBuilding);

    return 0;
}