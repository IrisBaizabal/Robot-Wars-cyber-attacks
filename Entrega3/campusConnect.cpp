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
    bool functional;
};

struct Node{
    int id;
    string name;
    string ip;
};

struct NSnap{
    string Name;
    vector<Edge> neighborEdge;
    int finalCost;
    bool functional;
};

bool useToCompare{
    // haha
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

