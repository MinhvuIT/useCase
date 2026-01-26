#ifndef FINE_H
#define FINE_H
#include <string>
using namespace std;

class Fine {
private:
    string fineid;
    string readerID;
    string bookID;
    double amount;
    string reason;

public:
    Fine(string fid = "", string rid = "", string bid = "", string r = "", int overdueDays = 0);
    
    // Getters
    string getFineID() const;
    string getReaderID() const;
    string getBookID() const;
    double getAmount() const;
    string getReason() const;
    
    // Methods
    double calculateFine(int overdueDays);
    void display() const;
    string toString() const;
    static Fine fromString(const string& line);
};
#endif
