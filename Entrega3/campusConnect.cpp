#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

const int inf = 999999;

class Node{
    public:
        char name;
        int x;
        int y;
    
    Node(){
        this->name = 0;
        this->x = 0;
        this->y = 0;
    }

    Node(char node_name, int x_location, int y_location){
        this->name = node_name;
        this->x = x_location;
        this->y = y_location;
    }

};

class Edge{
    public:
    char origin;
    char destiny;
    int value;

    Edge(){
        this->origin = 0;
        this->destiny = 0;
        this->value = 0;
    }

    Edge(char o, char d, int v){
        this->origin = o;
        this->destiny = d;
        this->value = v;;
    }
};
class Stack {
private:
    int* data;
    int top;
    int maxSize;

public:
    Stack(int capacity) {
        if (capacity <= 0) {
            capacity = 1;
        }
        maxSize = capacity;
        data = new int[maxSize];
        top = -1;
    }
    ~Stack() {
        delete[] data;
    }

    // O(1)
    bool isEmpty() {
        return top == -1;
    }

    // O(1)
    bool isFull() {
        return top == maxSize - 1;
    }

    // Inserts an element at the top of the stack
    // O(1), O(n) when resizing
    void push(int value) {
        if (isFull()) {
            int newSize = maxSize + 1;
            int* newData = new int[newSize];
            for (int i = 0; i <= top; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            maxSize = newSize;
        }
        data[++top] = value;
    }

    // Removes and returns the top element of the stack
    // O(1)
    int pop() {
        return data[top--];
    }
};

class Queue{
    private:
    int* data;
    int front;
    int end;
    int size;
    int maxSize;

    public:
    // Initializes the queue with a positive capacity
    // O(1)
    Queue(int capacity) {
        if (capacity <= 0){
            capacity = 1;
        }
        maxSize = capacity;
        data = new int[maxSize];
        front = -1;
        end = -1;
        size = 0;
    }

    // Releases the memory allocated for the queue
    // O(1)
    ~Queue() {
        delete[] data;
    }

    // Inserts an element at the end of the queue
    // O(1), O(n) when it needs to be resized
    void enqueue(int value) {
        if (isFull()) {
            int newSize = maxSize + 1;
            int* newData = new int[newSize];
            for (int i = 0; i < size; i++){
                newData[i] = data[(front + i) % maxSize];
            }
            delete[] data;
            data = newData;
            front = 0;
            end = size - 1;
            maxSize = newSize;
        }

        if (isEmpty()) {
            front = 0;
            end = 0;
        } else {
            end = (end + 1) % maxSize;
        }

        data[end] = value;
        size++;
    }

    // Removes and returns the front element of the queue
    // O(1)
    int dequeue() {
        int value = data[front];
        size--;

        if (isEmpty()) {
            front = -1;
            end = -1;
        } else {
            front = (front + 1) % maxSize;
        }

        return value;
    }
    
    // Returns the front element without removing it
    // O(1)
    int getFront() {
        return data[front];
    }

    // Checks if the queue is empty
    // O(1)
    bool isEmpty() {
        return size == 0;
    }

    // Checks if the queue is full
    // O(1)
    bool isFull() {
        return size == maxSize;
    }

    // Returns the numbers of elements in the queue
    // O(1)
    int getSize() {
        return size;
    }

};

string trimLine(string text){
    int start = 0;
    int end = (int)text.length()-1;

    while(start <= end && (text[start] == ' ' || text[start] == '\t' || text[start] == '\r' || text[start] == '\n')){
        start++;
    }
    while(end >= start && (text[end] == ' ' || text[end] == '\t' || text[end] == '\r' || text[end] == '\n')){
        end--;
    }

    if (start > end){
        return " ";
    }
    
    return text.substr(start, end - start + 1);
}

bool loadFile(string filename, Graph& graph, Edge*& fEdge, int& fCount, Node*& newNode, int& countNodes, Edge*& newEdges, int& countEdges){
    ifstream inFile(filename);
    if(!inFile.is_open()){
        return false;
    }

    string line = "";
    string section = "";
    bool headerRead = false;

    while(getline(inFile, line)){
        string clean = trimLine(line);
        if (clean != ""){
            if (clean[0] == '#'){
                if (clean.find("NEW_NODE") != string::npos){
                    section = "NEW_NODE";
                } else if (clean.find("NEW EDGE") != string::npos) {
                    section = "NEW_EDGES";
                } else if (clean.find("FAILED") != string::npos) {
                    section = "FAILED";
                } else if (clean.find("NODES") != string::npos) {
                    section = "NODES";
                } else if (clean.find("EDGES") != string::npos) {
                    section = "EDGES";
            }
        } else if (!headerRead && section == ""){
            int fNode = 0;
            int fEdge = 0;
            istringstream header(clean);
            header >> fNode >> fEdge;
            headerRead = true;
        } else if (section == "NODES"){
            string name = 0;
            int x = 0;
            int y = 0;
            istringstream iss(clean);
            if (iss >> name >> x >> y){
                //graph y .addnode implementation q falta
            }
        } else if (section == "EDGES"){
            string a = 0;
            string b = 0;
            int val = 0;
            istringstream iss(clean);
            if (iss>>a>>b>>val){
                // misma implementacion de graph q falta arriba con .addedge y segun q hay q poner byname
            }
        } else if (section == "FAILED") {
                string a = 0;
                string b = 0;
                istringstream iss(clean);
                if (iss >> a >> b) {
                    // implementación again
                }
            } else if (section == "NEW_NODE") {
                string name = "";
                int x = 0;
                int y = 0;
                istringstream iss(clean);
                if (iss >> name >> x >> y) {
                    //implementación againnnnnn
                }
            } else if (section == "NEW_EDGES") {
                string a = 0;
                string b = 0;
                int val = 0;
                istringstream iss(clean);
                if (iss >> a >> b >> val) {
                    // iris otra vez ponlo acá
                }
    }
}

void merge(, int left, int m, int right){
    int s1 = m - left + 1;
    int s2 = right - m;

    vector<Edge> L(s1);
    vector<Edge> R(s2);

    for (int i = 0; i < s1; i++) {
        L[i] = list[left + i];
    }
    for (int j = 0; j < s2; j++){
        R[j] = list[m + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while ( i < s1 && j < s2) {
        if (!R[j].useToCompare(L[i])){
            list[k] = L[i];
            i++;
        } else{
            list[k] = R[j];
            j++;
        }
        k++;
    }

    while ( i < s1){
        list[k] = L[i];
        i++;
        k++;
    }
    while (j < s2){
        list[k] = R[j];
        j++;
        k++;
    }
}

// Recursivity of merge sort for the registers of bitacora.
// Parameters: 
// left (integer) - left index of the arrangement to order.
// right (integer) - right index of the arrangement to order.
// Return: None.
// O(n log n)
void mergeSort(int left, int right ){
    if ( left < right ){
        int m = left + (right - left) / 2;
        mergeSort(left, m);
        mergeSort(m + 1, right);
        merge(list, m, right);
    }
}

int main(){

}