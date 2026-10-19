#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <string>

using namespace std;

//Class that represents the information of one line of the txt
//Stores the month, day, time, ip, reason of the line and timestamp and ipNumber used for comparison
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
            timestamp = timestamp();
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
        long long timestamp() const{
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
        Entry datos;
        Node* next;
        Node* prev;

        Node(Entry valor){
            datos = valor;
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
//Constructor of the class Stack, it creates an empty stack
//Parameters:none
//Return: none
//O(1)
        Stack(){
            topNode = nullptr;
        }
//Destructor of the class Stack. Frees all the nodes that remain in the stack.
//Parameters: none
//Return: none
//O(n)
        ~Stack(){
            while (!isEmpty()){
                pop();
            }
        }
//Checks if the stack is empty
//Parameters: none
//Return: Boolean, true if the stack has no elements.
//O(1)
        bool isEmpty() const{
            return topNode == nullptr;
        }
//Adds a range (low, high) to the top of the stack
//Parameters: low (Node*): first node of the range, high (Node*): last node of the range
//Return: none
//O(1)
        void push(Node* low, Node* high){
            StackNode* nNode = new StackNode(low, high);
            nNode->next = topNode;
            topNode = nNode;
        }
//Removes the range at the top of the stack and returns it through the parameters
//Parameters: low (Node*): receives the first node of the removed range, high (Node*): receives the last node of the removed range
//Return: Boolean, true if an element was removed or if its empty returns false
//O(1)
        bool pop(Node* low, Node* high){
            if (isEmpty()){
                return false;
            }
            low = topNode->low;
            high = topNode->high;
            StackNode* help = topNode;
            topNode = topNode->next;

            return true;
        }
};
//Class that stores all the entries of the log in a doubly linked list and sorts them by IP and timestamp using Quick Sort
class SystemLog{
    private:
        Node* head;
        Node* tail;
        int counter;
//Swaps the Entry stored in two nodes (the nodes stay in place, only the data moves)
//Parameters: a (Node*): first node, b (Node*): second node
//Return: none
//O(1)
        void swapData(Node* a, Node* b) {
            Entry temp = a->data;
            a->data = b->data;
            b->data = temp;
        }
//Partition step of Quick Sort
//Parameters: low (Node*): first node of the range to partition, high (Node*): last node of the range (the pivot)
//Return: Node* with the final position of the pivot
//O(k), where k is the number of nodes in the range [low, high]
        Node* partition(Node* low, Node* high) {
            Entry pivot = high->data;
            Node* i = low->prev;

            for (Node* j = low; j != high; j = j->next) {
                if (j->data.useToCompare(pivot)) {
                    i = (i == nullptr) ? low : i->next;
                    swapData(i, j);
                }
            }
            i = (i == nullptr) ? low : i->next;
            swapData(i, high);
            return i;
        }



    public:
//Constructor of the class SystemLog, creates an empty list
//Parameters: none
//Return: none
//O(1)
        SystemLog(){
            head = nullptr;
            tail = nullptr;
            counter = 0;
        }
//Destructor of the class SystemLog, frees all the nodes of the list
//Parameters: none
//Return: none
//O(n) 
        ~SystemLog(){
            Node* current = head;
            while (current != nullptr){
                Node* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }
//Adds a new entry at the end of the list
//Parameters: entry (const Entry&)
//Return: nothing
//O(1)
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
//Sorts the whole list by IP and, for equal IPs, by timestamp, uses an iterative Quick Sort
//Parameters: none
//Return: nothing
//Average case: O(n log n), Worst case: O(n^2)
        void quickSort(){
            if (head != nullptr){
                Stack stack;
                stack.push(head, tail);

                Node* low = nullptr;
                Node* high = nullptr;

                while(stack.pop(low, high)){
                    if (high != nullptr && low != high && low != high->next){
                        Node* pivote = partir(low, high);

                        if (pivote != nullptr && pivote != low){
                            stack.push(low, pivote->prev);
                        }

                        if (pivote != nullptr && pivote !=high){
                            stack.push(pivote->next, high);
                        }
                    }
                }
                cout <<"Data sorted with IP and Timestamp with Quick Sort.";
            }
        }

};

class SystemLog{

};

int main(){

}
