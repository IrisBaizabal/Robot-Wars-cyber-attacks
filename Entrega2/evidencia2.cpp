#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <string>

using namespace std;


class Entry{
    private:
        string month;
        int day;
        string time;
        string ip;
        string reason;
        long long timestamp;
        long long ipNumber;

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
            timestamp = 0;
            ipNumber = 0;
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
            timestamp = timestamps();
            ipNumber = ipToNumber(ip);
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

        long long getTimestamp() const{
            return timestamp;
        }

        long long getIpNumber() const {
            return ipNumber;
        }

        // Converter of the abbreviated name of the month to its equivalent in number.
        // Parameters: monthName (const string&) - Abbreviation of the month to be converted.
        // Return: Integer corresponding to the month's number.
        // O(1)
        int monthToNumber(const string& monthName) const {
            static const string monthNames[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
            int monthNumber = 0;
            int index = 0;

            while (index < 12 && monthNumber == 0) {
                if (monthNames[index] == monthName) {
                    monthNumber = index + 1;
                }
                index++;
            }
            return monthNumber;
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
        
        // Calculates the timestamp combining month, day and time in seconds.
        // O (1)
        long long timestamps() const{
            long long m = monthToNumber(month);
            long d = day;
            long long s = stringTimeToInteger(time);
            return(m * 31LL * 86400LL) + (d * 86400LL) + s;
        }

        // Converts an IP into an integer by by padding each octet to 3 digits.
        // O(1)
        static long long ipToNumber(const string& ip) {
            int o1 = 0, o2 = 0, o3 = 0, o4 = 0;
            if (sscanf(ip.c_str(), "%d.%d.%d.%d", &o1, &o2, &o3, &o4) == 4) {
                return (long long)o1 * 1000000000LL + (long long)o2 * 1000000LL + (long long)o3 * 1000LL + (long long)o4;
            }
            return 0;
        }

        // Compares the actual object with other Entry object cronologically.
        // Parameters: Other (Entry) - By reference to the object Entry to compare.
        // Return: Boolean value, if the actual object happens before other.
        // O(1)
        bool useToCompareIp(const Entry& other) const{
            if (ipNumber != other.ipNumber){
                return ipNumber < other.ipNumber;
            }
            return timestamp <= other.timestamp;
        }

        // Create the line with the entry values.
        // Parameters: None.
        // Return: String to save with the data.
        // O(1)
        string logLine() const {
            return month + " " + to_string(day) + " " + time + " " + ip + " " + reason;
        }

};

class Node {
    public: 
        Entry data;
        Node* next;
        Node* prev;

        Node(Entry valor){
            data = valor;
            next = nullptr;
            prev = nullptr;
        }
};

struct StackNode {
    Node* address;
    StackNode* next;

    // Constructor of the struct StackNode.
    // Parameters: nodeAddress (Node*) - Memory address of a Node in the doubly linked list.
    // Return: None.
    // O(1)
    StackNode(Node* nodeAddress) {
        address = nodeAddress;
        next = nullptr;
    }
};

class Stack{
    private: 
        StackNode* topNode;
    
    public:
        Stack(){
            topNode = nullptr;
        }

        ~Stack(){
            while (!isEmpty()){
                pop();
            }
        }
    
        bool isEmpty() const{
            return topNode == nullptr;
        }

        void push(Node* address) {
            StackNode* newNode = new StackNode(address);
            newNode->next = topNode;
            topNode = newNode;
        }

        Node* pop() {
            if (isEmpty()) {
                return nullptr;
            }
            StackNode* help = topNode;
            Node* address = topNode->address;
            topNode = topNode->next;
            delete help;
            return address;
        }
};

class SystemLog{
    private:
        Node* head;
        Node* tail;
        int counter;

        void swapData(Node* a, Node* b) {
            Entry temp = a->data;
            a->data = b->data;
            b->data = temp;
        }

        Node* partition(Node* low, Node* high) {
            Entry pivot = high->data;
            Node* i = low->prev;

            for (Node* j = low; j != high; j = j->next) {
                if (j->data.useToCompareIp(pivot)) {
                    i = (i == nullptr) ? low : i->next;
                    swapData(i, j);
                }
            }
            i = (i == nullptr) ? low : i->next;
            swapData(i, high);
            return i;
        }



    public:
        SystemLog(){
            head = nullptr;
            tail = nullptr;
            counter = 0;
        }
        
        ~SystemLog(){
            Node* current = head;
            while (current != nullptr){
                Node* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }

        void addEntry(const Entry& entry){
            Node* newNode = new Node(entry);
            if (head == nullptr){
                head = newNode;
                tail = newNode;
            } else{
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            counter++;
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
                addEntry(entry);
            }

            readFile.close();
            cout << counter << " records loaded" << endl;
        }

        void quickSort() {
            if (head != nullptr && head != tail) {
                Stack stack;
                stack.push(head);
                stack.push(tail);

                while (!stack.isEmpty()) {
                    Node* high = stack.pop();
                    Node* low = stack.pop();

                    if (low != nullptr && high != nullptr && low != high && low != high->next) {
                        Node* pivot = partition(low, high);

                        if (pivot != nullptr && pivot != low && low != pivot->prev) {
                            stack.push(low);
                            stack.push(pivot->prev);
                        }

                        if (pivot != nullptr && pivot != high && high != pivot->next) {
                            stack.push(pivot->next);
                            stack.push(high);
                        }
                    }
                }
                cout << "Data sorted." << endl;
            }
        }

        void searchAndExport(string startIp, string endIp, string outFilename = "output.txt") const {
            long long minIp = Entry::ipToNumber(startIp);
            long long maxIp = Entry::ipToNumber(endIp);

            if (minIp > maxIp) {
                long long temp = minIp;
                minIp = maxIp;
                maxIp = temp;
            }

            ofstream outFile(outFilename);
            int recordCount = 0;

            Node* current = head;
            while (current != nullptr) {
                long long currentIp = current->data.getIpNumber();

                if (currentIp >= minIp && currentIp <= maxIp) {
                    outFile << current->data.logLine() << "\n";
                    cout << current->data.logLine() << endl;
                    recordCount++;
                } else if (currentIp > maxIp) {
                    break;
                }
                current = current->next;
            }

            outFile.close();
            if (recordCount > 0) {
                cout << recordCount << " records found and exported to '" << outFilename << "'" << endl;
            } else {
                cout << "No records were found in the specified IP range." << endl;
            }
        }

};


int main() {
    SystemLog systemLog;
    systemLog.loadFile();
    systemLog.quickSort();

    string startIp = "";
    string endIp = "";

    cout << "Enter the starting IP address (For example: 108.57.27.85): ";
    cin >> startIp;

    cout << "Enter the ending IP address (For example: 423.2.230.77): ";
    cin >> endIp;

    systemLog.searchAndExport(startIp, endIp, "output.txt");

    return 0;
}