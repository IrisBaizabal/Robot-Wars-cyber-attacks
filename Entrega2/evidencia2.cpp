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
        string logLine() const {
            return month + " " + to_string(day) + " " + time + " " + ip + " " + reason;
        }

};

struct Node {
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
    Node* low;
    Node* high;
    StackNode* next;

    StackNode(Node* lowNode, Node* highNode){
        low = lowNode;
        high = highNode;
        next = nullptr;
    }
};

class StackConstructor {
    private: 
        StackNode* nodoSuperior;
    
    public:
        StackConstructor(){
            nodoSuperior = nullptr;
        }
    
        bool vacio() const{
            return nodoSuperior == nullptr;
        }

        void push(Node* low, Node* high){
            StackNode* nNode = new StackNode(low, high);
            nNode->next = nodoSuperior;
            nodoSuperior = nNode;
        }

        bool pop(Node* low, Node* high){
            if (!vacio()){
                return false;
            }
            low = nodoSuperior->low;
            high = nodoSuperior->high;
            StackNode* help = nodoSuperior;
            nodoSuperior = nodoSuperior->next;

            return true;
        }
};

class SystemLog{
    private:
        Node* head;
        Node* tail;
        int contador;

        // no se hacer esto lol ayuda iris baizabal
        Node* partir(Node* low, Node* high){
            Entry pivote;
        }

    public:
        SystemLog(){
            head = nullptr;
            tail = nullptr;
            contador = 0;
        }
        
        ~SystemLog(){
            Node* current = head;
            while (current != nullptr){
                Node* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }

        void quickSort(){
            if (head != nullptr){
                StackConstructor stack;
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