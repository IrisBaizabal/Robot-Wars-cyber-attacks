#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

class Entry{
    private:
        string month;
        int day;
        int hour;
        string ip;
        string reason;

    public:
    int monthToNumber(string month){
        map<string, int> months{
            {"Jun", 6},{"Jul", 7},{"Aug", 8},{"Sep", 9},{"Oct", 10}
        };
        return months[month];
    }
};

int main(){
    string myLine = "";
    ifstream readFile("bitacora.txt");
    Entry testCase;

    cout << testCase.monthToNumber("Jul");

    readFile.close();
    return 0;
}