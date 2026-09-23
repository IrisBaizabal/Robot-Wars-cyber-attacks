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
        string time;
        string ip;
        string reason;

    public:
        Entry(){
            month = "";
            day = 0;
            time = "";
            ip = "";
            reason = "";
        }

        Entry(string Month, int Day, string Time, string Ip, string Reason){
            month = Month;
            day = Day;
            time = Time;
            ip = Ip;
            reason = Reason;
        }

        string getMonth() const{
            return month;
        }
        int getDay() const{
            return day;
        }
        string getTime() const{
            return time;
        }
        string getIp() const{
            return ip;
        }
        string getReason() const{
            return reason;
        }

        int monthToNumber(string month){
            map<string, int> months{
                {"Jun", 6},{"Jul", 7},{"Aug", 8},{"Sep", 9},{"Oct", 10}
            };
            return months[month];
        }
};

class Bitacora{
    private:
        vector<Entry> guardado;

    public:
        void loadFile(){
            string myLine = "";
            ifstream readFile("bitacora.txt");

            while(getline(readFile, myLine)){
                string month;
                int day;
                string time;
                string ip;
                string reason;
                
                stringstream ss(myLine);
                ss >> month >> day >> time >> ip;
                getline(ss >> ws, reason);

                Entry entry(month, day, time, ip, reason);
                guardado.push_back(entry);
            }
            readFile.close();
            cout << guardado.size() << " records loaded" <<endl;
        };

};

int main(){
    // Entry testCase;
    // cout << testCase.monthToNumber("Jul") << endl;

    Bitacora bitacora;
    bitacora.loadFile();

    
    return 0;
}