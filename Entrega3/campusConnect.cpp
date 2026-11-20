#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;


class Node{
    public:
        char name;
        int x;
        int y;
    
    Node(){
        this->name = 0.0;
        this->x = 0;
        this->y = 0;
    }

    Node(char, int, int){
        this
    }

};

class Stack {
private:
    int* data;
    int top;
    int maxSize;

public:
    // Initializes the stack with a positive capacity
    // O(1)
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



void merge(vector<Edge> list, int left, int m, int right){
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

void loadFile(){
    string myLine = "";
    ifstream readFile("bitacora.txt");

    while(getline(readFile, myLine)){
        string month = "";
        int day = 0;
        string time = "";
        string ip = "";
        string reason = "" ;
        
        stringstream ss(myLine);
        ss >> month >> day >> time >> ip;
        getline(ss >> ws, reason);

        if (!reason.empty() && reason.back() == '\r') {
            reason.pop_back();
        }

        Entry entry(month, day, time, ip, reason);
        logEntries.push_back(entry);

    }
    readFile.close();
    cout << logEntries.size() << " records loaded" <<endl;
}

int main(){

}