#include "Fine.h"
#include <iostream>
#include <sstream>
using namespace std;

Fine::Fine(string fid, string rid, string bid, string r, int overdueDays) 
    : fineid(fid), readerID(rid), bookID(bid), reason(r) {
    amount = calculateFine(overdueDays);
}

double Fine::calculateFine(int overdueDays) {
    // Theo dac ta:
    // - Qua han trong 3 ngay: 15000 VND/quyen
    // - Qua han hon 3 ngay: 15000 + 5000 * (so ngay qua han - 3)
    // - Sach hu hong: 35000 VND/quyen
    // - Mat sach: 75000 VND/quyen
    
    if (reason == "Overdue" || reason == "Qua han") {
        if (overdueDays <= 0) return 0;
        if (overdueDays <= 3) return 15000;
        return 15000 + (overdueDays - 3) * 5000;
    }
    if (reason == "Damaged" || reason == "Hu hong") {
        return 35000;
    }
    if (reason == "Lost" || reason == "Mat sach") {
        return 75000;
    }
    return 0;
}

string Fine::getFineID() const {
    return fineid;
}

string Fine::getReaderID() const {
    return readerID;
}

string Fine::getBookID() const {
    return bookID;
}

double Fine::getAmount() const {
    return amount;
}

string Fine::getReason() const {
    return reason;
}

void Fine::display() const {
    cout << "Ma phat: " << fineid 
         << " | Doc gia: " << readerID
         << " | Sach: " << bookID
         << " | So tien: " << amount << " VND"
         << " | Ly do: " << reason << endl;
}

string Fine::toString() const {
    stringstream ss;
    ss << fineid << ";" << readerID << ";" << bookID << ";" << amount << ";" << reason;
    return ss.str();
}

Fine Fine::fromString(const string& line) {
    stringstream ss(line);
    string fid, rid, bid, amountStr, r;
    getline(ss, fid, ';');
    getline(ss, rid, ';');
    getline(ss, bid, ';');
    getline(ss, amountStr, ';');
    getline(ss, r, ';');
    
    Fine f(fid, rid, bid, r, 0);
    // Set amount directly from loaded value
    return f;
}
