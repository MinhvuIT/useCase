// ================= BorrowSlip.h =================
#ifndef BORROWSLIP_H
#define BORROWSLIP_H
#include <string>
#include <ctime>
using namespace std;

class BorrowSlip {
private:
    string slipid;
    string readerID;
    string bookID;
    string bookTitle;
    string bookCondition;
    time_t borrowDate;
    time_t dueDate;
    time_t returnDate;
    bool returned;

public:
    BorrowSlip(string sid = "", string rid = "", string bid = "", string title = "", string condition = "Tot");

    // Getters
    string getSlipID() const;
    string getBookID() const;
    string getReaderID() const;
    string getBookTitle() const;
    string getBookCondition() const;
    time_t getBorrowDate() const;
    time_t getDueDate() const;
    time_t getReturnDate() const;
    bool isReturned() const;

    // Setters (de khoi phuc tu file)
    void setBorrowDate(time_t date);
    void setDueDate(time_t date);
    void setReturnDate(time_t date);
    void setReturned(bool status);

    // Methods
    void markReturned();
    bool isOverdue() const;
    int getOverdueDays() const;
    void display() const;
    string toString() const;
    static BorrowSlip fromString(const string& line);
};
#endif
