#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cstdio>

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

        int monthToNumber(string month)const{
            map<string, int> months{
                {"Jan", 1},{"Feb", 2},{"Mar", 3},{"Apr", 4},{"May", 5},{"Jun", 6},{"Jul", 7},{"Aug", 8},{"Sep", 9},{"Oct", 10},{"Nov", 11},{"Dec", 12}
            };
            return months[month];
        }

        int stringTimeToInteger(string time)const{
            int hours = 0;
            int minutes = 0;
            int seconds = 0;
            int totalSeconds = 0;

            if (sscanf(time.c_str(), "%d:%d:%d", &hours, &minutes, &seconds) == 3){
                totalSeconds = hours * 3600 + minutes * 60 + seconds;
            }
            return totalSeconds;
        }

        bool useToCompare(const Entry& other) const{
            int month1 = monthToNumber(month);
            int month2 = monthToNumber(other.month);

            if (month1 != month2){
                return month1 < month2;
            }

            if (day != other.day){
                return day < other.day;
            }

            return stringTimeToInteger(time) < other.stringTimeToInteger(other.time);
        }

        string bitacoraline() const {
            return month + " " + to_string(day) + " " + time + " " + ip + " " + reason;
        }

};

class Bitacora{
    private:
        vector<Entry> guardado;

        void merge(int left, int m, int right){
            int s1 = m - left + 1;
            int s2 = right - m;

            vector<Entry> L(s1);
            vector<Entry> R(s2);

            for (int i = 0; i < s1; i++) {
                L[i] = guardado[left + i];
            }
            for (int j = 0; j < s2; j++){
                R[j] = guardado[m + 1 + j];
            }

            int i = 0;
            int j = 0;
            int k = left;

            while ( i < s1 && j < s2) {
                if (L[i].useToCompare(R[j])){
                    guardado[k] = L[i];
                    i++;
                } else{
                    guardado[k] = R[j];
                    j++;
                }
                k++;
            }

            while ( i < s1){
                guardado[k] = L[i];
                i++;
                k++;
            }
            while (j < s2){
                guardado[k] = R[j];
                j++;
                k++;
            }
        }

        void mergeSort(int left, int right ){
            if ( left < right ){
                int m = left + (right - left) / 2;
                mergeSort(left, m);
                mergeSort(m + 1, right);
                merge(left, m, right);
            }
        }


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

        void sortData(){
            if(!guardado.empty()){
                mergeSort(0, guardado.size()-1);
                cout << "Data correctly sorted" << endl;
            }
        }

        void searchAndExport (string startMonth, int startDay, string endMonth, int endDay){
            Entry startTarget(startMonth, startDay, "00:00:00", "", "");
            Entry endTarget(endMonth, endDay, "23:59:59", "", "");

            int startIndex = -1;
            int endIndex = -1;
            int low = 0;
            int high = guardado.size() -1;

            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (guardado[mid].useToCompare(startTarget)) {
                    low = mid + 1; 
                } else {
                    startIndex = mid;
                    high = mid - 1;
                }
            }

            low = 0; 
            high = guardado.size() - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (endTarget.useToCompare(guardado[mid])) {
                    high = mid - 1; 
                } else {
                    endIndex = mid; 
                    low = mid + 1;
                }
            }

            if (startIndex != -1 && endIndex != -1 && startIndex <= endIndex) {
                ofstream outFile("results.txt");
                int recordCount = 0;
                
               
                for (int i = startIndex; i <= endIndex; i++) {
                    outFile << guardado[i].bitacoraline() << "\n";
                    recordCount++;
                }
                
                outFile.close();
                cout << recordCount << " records found and exported to 'results.txt'" << endl;
            } else {
                cout << "No records were found in the specified date range." << endl;
            }
        }

};

int main(){
    Bitacora bitacora;
    bitacora.loadFile();
    bitacora.sortData();
    
    string startMonth;
    string endMonth;
    int startDay;
    int endDay;

    cout << "Enter the start date (For example: Aug 14): ";
    cin >> startMonth >> startDay; 

    cout << "Enter the end date (For example: Sep 10): ";
    cin >> endMonth >> endDay;

    bitacora.searchAndExport(startMonth, startDay, endMonth, endDay);

    return 0;



    return 0;
}