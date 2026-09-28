// Evidence 1 - Problem situation
// Created: 22/09/2026
// Finished: 27/09/2026
// Authors: 
// Carmen Iris Vazquez Baizabal - A00843705
// Francisco Santos Martinez Ortiz - A00843605
// Erika Esquivel Correa - A00841206
// This program reads a text file called "bitacora.txt" to sort it
// cronologically and the user can export another text file with the
// attempts to log in a specific range of dates.
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
        // Default constructor of the class Entry.
        // Initialize the atributes with a zero or empty.
        // Parameters: None.
        // Return: None
        // O(1)
        Entry(){
            month = "";
            day = 0;
            time = "";
            ip = "";
            reason = "";
        }

        // Constructor with parameters of the class Entry.
        // Initialize with specific values.
        // Parameters: 
        // Month (string) - month of the event.
        // Day (integer) - day of the event.
        // Time (string) - hour of the event in format HH:MM:SS.
        // Ip (string) - IP address of the device.
        // Reason (string) - Reason of the event.
        // Return: Nothing.
        // O(1)
        Entry(string Month, int Day, string Time, string Ip, string Reason){
            month = Month;
            day = Day;
            time = Time;
            ip = Ip;
            reason = Reason;
        }

        // Get the month of the event.
        // Parameters: None.
        // Return: String with the month of the event.
        // O(1)
        string getMonth() const{
            return month;
        }

        // Get the day of the event.
        // Parameters: None.
        // Return: Integer with the day of the event.
        // O(1)
        int getDay() const{
            return day;
        }

        // Get the time of the event.
        // Parameters: None.
        // Return: String with the time (HH:MM:SS) of the event.
        // O(1)
        string getTime() const{
            return time;
        }

        // Get the IP of the event.
        // Parameters: None.
        // Return: String with the IP of the event.
        // O(1)
        string getIp() const{
            return ip;
        }

        // Get the reason of the event.
        // Parameters: None.
        // Return: String with the reason of the event.
        // O(1)
        string getReason() const{
            return reason;
        }

        // Converter of the abbreviated name of the month to its equivalent in number.
        // Parameters: month (string) - Abbreviaton of the month to be converted.
        // Return: Integer corresponding to the month's number.
        // O(1)
        int monthToNumber(string month)const{
            map<string, int> months{
                {"Jan", 1},{"Feb", 2},{"Mar", 3},{"Apr", 4},{"May", 5},{"Jun", 6},{"Jul", 7},{"Aug", 8},{"Sep", 9},{"Oct", 10},{"Nov", 11},{"Dec", 12}
            };
            return months[month];
        }

        // Convert the string of time (HH:MM:SS) to its equivalent in seconds for comparing.
        // Parameters: time (string) - Line with the hour in format (HH:MM:SS).
        // Return: Integer with the equivalent in seconds of the given hour.
        // O(1)
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

        // Compares the actual object with other Entry object cronologically.
        // Parameters: Other (Entry) - By reference to the object Entry to compare.
        // Return: Boolean value, if the actual object happens before other.
        // O(1)
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

        // Create the line with the entry values.
        // Parameters: None.
        // Return: String to save with the data.
        // O(1)
        string bitacoraline() const {
            return month + " " + to_string(day) + " " + time + " " + ip + " " + reason;
        }

};

class Bitacora{
    private:
        vector<Entry> guardado;

        // Merge to arrangements ordered in the entries vector.
        // Parameters: 
        // left (integer): Left index of the first arrangement.
        // m (integer): Middle index that divides both arrangements.
        // right (integer): Right index of the second arrangement.
        // Return: None.
        // O(n)
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
                if (!R[j].useToCompare(L[i])){
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
                merge(left, m, right);
            }
        }


    public:
        // Read the registers of the file "bitacora.txt" and stores it in a vector.
        // Parameters: None.
        // Return: None.
        // O(n)
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
                guardado.push_back(entry);

            }
            readFile.close();
            cout << guardado.size() << " records loaded" <<endl;
        }

        // Call mergeSort for the saved registers.
        // Parameters: None.
        // Return: None.
        // O(n log n)
        void sortData(){
            if(!guardado.empty()){
                mergeSort(0, guardado.size()-1);
                cout << "Data correctly sorted" << endl;
            }
        }

        // Search using binary search with the entry of a range of dates and exports it to "results.txt".
        // Parameters:
        // startMonth (string): Initial month of the range.
        // startDay (integer): Initial day of the range.
        // endMonth (string): Last month of the range.
        // endDay (integer): Last day of the range.
        // Return: None.
        // O(log n + k)
        void searchAndExport (string startMonth, int startDay, string endMonth, int endDay){
            Entry startTarget(startMonth, startDay, "00:00:00", "", "");
            Entry endTarget(endMonth, endDay, "23:59:59", "", "");

            int startIndex = -1;
            int endIndex = -1;
            int low = 0;
            int high = guardado.size() -1;

            // Binary search of the initial index.
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

            // Binary search of the last index.
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
                    cout << guardado[i].bitacoraline() << endl;
                    recordCount++;
                }
                
                outFile.close();
                cout << recordCount << " records found and exported to 'results.txt'" << endl;
            } else {
                cout << "No records were found in the specified date range." << endl;
            }
        }

};

 // Main function of the program.
 // Parameters: None.
 // Return: 0.
 // O(n log n)
int main(){
    Bitacora bitacora;
    bitacora.loadFile();
    bitacora.sortData();
    
    string startMonth = "";
    string endMonth = "";
    int startDay = 0;
    int endDay = 0;

    cout << "Enter the start date (For example: Aug 14): ";
    cin >> startMonth >> startDay; 

    cout << "Enter the end date (For example: Sep 10): ";
    cin >> endMonth >> endDay;

    bitacora.searchAndExport(startMonth, startDay, endMonth, endDay);

    return 0;

}