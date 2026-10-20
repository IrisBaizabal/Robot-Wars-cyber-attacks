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

        // O(1)
        string getMonth() const{
            return month;
        }

        // O(1)
        int getDay() const{
            return day;
        }

        // O(1)
        string getTime() const{
            return time;
        }

        // O(1)
        string getIp() const{
            return ip;
        }

        // O(1)
        string getReason() const{
            return reason;
        }

        // O(1)
        long long getTimestamp() const{
            return timestamp;
        }

        // O(1)
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
        // Parameters: None
        // Return: Long long with the equal of time in seconds.
        // O(1)
        long long timestamps() const{
            long long m = monthToNumber(month);
            long d = day;
            long long s = stringTimeToInteger(time);
            return(m * 31LL * 86400LL) + (d * 86400LL) + s;
        }

        // Converts an IP into an integer by by padding each octet to 3 digits.
        // Parameters: IP address.
        // Return: Long long with the equal of IP number
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

        // Compare if a date happened before other.
        // Parameters: Other date.
        // Return: True if the event happened before the second (other) one.
        //         False if the event happened after the second (other) one.
        // O(1)
        bool useToCompareDate(const Entry& other) const {
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

        // Default constructor of the class Node.
        // Initialize the atributes with a zero or empty.
        // Parameters: Value of the node.
        // Return: None
        // O(1)
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

        // Default constructor of the class stack.
        // Parameters: None.
        // Return: None
        // O(1)
        Stack(){
            topNode = nullptr;
        }

        // Default destructor of the class stack.
        // Parameters: None.
        // Return: None
        // O(n)
        ~Stack(){
            while (!isEmpty()){
                pop();
            }
        }
    
        // Checks if something is empty.
        // Parameters: None.
        // Return: None
        // O(1)
        bool isEmpty() const{
            return topNode == nullptr;
        }

        // Inserter of elements of the pile.
        // Parameters: Pointer with the address of node.
        // Return: None
        // O(1)
        void push(Node* address) {
            StackNode* newNode = new StackNode(address);
            newNode->next = topNode;
            topNode = newNode;
        }

        // Get out the Node* and deleting the stacknode.
        // Parameters: None.
        // Return: Address of popped element.
        // O(1)
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

        // Swapper of elements with pointers.
        // Parameters: Addresses of the elements (2) to be swapped.
        // Return: None.
        // O(1)
        void swapData(Node* a, Node* b) {
            Entry temp = a->data;
            a->data = b->data;
            b->data = temp;
        }

        // Partition to use in quick sort.
        // Parameters: Pointer of lowest element, highest and the boolean value of IP use.
        // Return: Index of next pivot.
        // O(1)
        Node* partition(Node* low, Node* high, bool byIp) {
            Entry pivot = high->data;
            Node* i = low->prev;

            for (Node* j = low; j != high; j = j->next) {
                if (byIp ? j->data.useToCompareIp(pivot)
                        : j->data.useToCompareDate(pivot)) {
                    i = (i == nullptr) ? low : i->next;
                    swapData(i, j);
                }
            }

            i = (i == nullptr) ? low : i->next;
            swapData(i, high);
            return i;
        }



    public:
        // Default constructor of the class SystemLog.
        // Parameters: None.
        // Return: None
        // O(1)
        SystemLog(){
            head = nullptr;
            tail = nullptr;
            counter = 0;
        }
        
        // Default destructor of the class SystemLog.
        // Parameters: None.
        // Return: None
        // O(n)
        ~SystemLog(){
            Node* current = head;
            while (current != nullptr){
                Node* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }

        // Adds a new entry to the system log.
        // Parameters: Reference of entry class.
        // Return: None
        // O(1)
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

        // Loads log entries with the txt.
        // Parameters: None.
        // Return: None
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
                addEntry(entry);
            }

            readFile.close();
            cout << counter << " records loaded" << endl;
        }

        // Quick sort to organize byIp.
        // Parameters: True or false if it uses IP.
        // Return: None
        // O(n log n)
        void quickSort(bool byIp) {
            if (head != nullptr && head != tail) {
                Stack stack;
                stack.push(head);
                stack.push(tail);

                while (!stack.isEmpty()) {
                    Node* high = stack.pop();
                    Node* low = stack.pop();

                    if (low != nullptr && high != nullptr && low != high && low != high->next) {
                        Node* pivot = partition(low, high, byIp);

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
                if (byIp) {
                    cout << "Data sorted by IP." << endl;
                } else {
                    cout << "Data sorted by Date." << endl;
                }
            }
        }    

        // Exports the IP register of matches.
        // Parameters: Starter IP (string), end IP (string), name of the output txt (string).
        // Return: None
        // O(n)
        void searchAndExportIp(string startIp, string endIp, string outFilename = "output.txt") const {
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

        // Exporter by date the matches.
        // Parameters: Start month (string), start day of date (int), end month of date (string), end day of date (int), output file name (string).
        // Return: None
        // O(n)
        void searchAndExportDate(string startMonth, int startDay, string endMonth, int endDay, string outFilename = "output.txt") const {
            Entry startTarget(startMonth, startDay, "00:00:00", "", "");
            Entry endTarget(endMonth, endDay, "23:59:59", "", "");

            long long minTime = startTarget.getTimestamp();
            long long maxTime = endTarget.getTimestamp();

            if (minTime > maxTime) {
                long long temp = minTime;
                minTime = maxTime;
                maxTime = temp;
            }

            ofstream outFile(outFilename);
            int recordCount = 0;

            Node* current = head;
            while (current != nullptr) {
                long long currentTime = current->data.getTimestamp();

                if (currentTime >= minTime && currentTime <= maxTime) {
                    outFile << current->data.logLine() << "\n";
                    cout << current->data.logLine() << endl;
                    recordCount++;
                } else if (currentTime > maxTime) {
                    break;
                }
                current = current->next;
            }

            outFile.close();
            if (recordCount > 0) {
                cout << recordCount << " records found and exported to '" << outFilename << "'" << endl;
            } else {
                cout << "No records were found in the specified date range." << endl;
            }
        }
};

// Main program.
// Parameters: None.
// Return: 0 (and txt file of desired format, ip or date).
// O(n log n)
int main() {
    SystemLog systemLog;
    systemLog.loadFile();

    string option = "";
    cout << "How do you want to sort and search the data? ('ip' or 'date'): ";
    cin >> option;

    if (option == "date" || option == "Date" || option == "DATE") {
        systemLog.quickSort(false);

        string startMonth = "";
        string endMonth = "";
        int startDay = 0;
        int endDay = 0;

        cout << "Enter the start date (For example: Aug 14): ";
        cin >> startMonth >> startDay;

        cout << "Enter the end date (For example: Sep 10): ";
        cin >> endMonth >> endDay;

        systemLog.searchAndExportDate(startMonth, startDay, endMonth, endDay, "testCase3.txt");
    } else if (option == "ip" || option == "Ip" || option == "IP"){
        systemLog.quickSort(true);

        string startIp = "";
        string endIp = "";

        cout << "Enter the starting IP address (For example: 108.57.27.85): ";
        cin >> startIp;

        cout << "Enter the ending IP address (For example: 423.2.230.77): ";
        cin >> endIp;

        systemLog.searchAndExportIp(startIp, endIp, "testCase3.txt");
    } else{
        cout << "Option not valid" << endl;
    }

    return 0;
}
