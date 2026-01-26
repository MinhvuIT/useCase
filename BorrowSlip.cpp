#include "BorrowSlip.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

BorrowSlip::BorrowSlip(string sid, string rid, string bid, string title, string condition)
    : slipid(sid), readerID(rid), bookID(bid), bookTitle(title), bookCondition(condition), 
      returnDate(0), returned(false) {
    borrowDate = time(0);
    dueDate = borrowDate + 7 * 24 * 3600; // Han tra 7 ngay
}

string BorrowSlip::getSlipID() const {
    return slipid;
}

string BorrowSlip::getBookID() const {
    return bookID;
}

string BorrowSlip::getReaderID() const {
    return readerID;
}

string BorrowSlip::getBookTitle() const {
    return bookTitle;
}

string BorrowSlip::getBookCondition() const {
    return bookCondition;
}

time_t BorrowSlip::getBorrowDate() const {
    return borrowDate;
}

time_t BorrowSlip::getDueDate() const {
    return dueDate;
}

time_t BorrowSlip::getReturnDate() const {
    return returnDate;
}

bool BorrowSlip::isReturned() const {
    return returned;
}

void BorrowSlip::markReturned() {
    returned = true;
    returnDate = time(0);
}

// Setters de khoi phuc tu file
void BorrowSlip::setBorrowDate(time_t date) {
    borrowDate = date;
}

void BorrowSlip::setDueDate(time_t date) {
    dueDate = date;
}

void BorrowSlip::setReturnDate(time_t date) {
    returnDate = date;
}

void BorrowSlip::setReturned(bool status) {
    returned = status;
}

bool BorrowSlip::isOverdue() const {
    time_t now = time(0);
    if (returned) {
        return returnDate > dueDate;
    }
    return now > dueDate;
}

int BorrowSlip::getOverdueDays() const {
    time_t checkTime = returned ? returnDate : time(0);
    if (checkTime <= dueDate) return 0;
    return static_cast<int>((checkTime - dueDate) / (24 * 3600));
}

void BorrowSlip::display() const {
    char borrowStr[20], dueStr[20], returnStr[20];
    struct tm timeInfo;

    // Su dung localtime_s (phien ban an toan cho Windows)
    localtime_s(&timeInfo, &borrowDate);
    strftime(borrowStr, 20, "%d/%m/%Y", &timeInfo);

    localtime_s(&timeInfo, &dueDate);
    strftime(dueStr, 20, "%d/%m/%Y", &timeInfo);

    cout << "Ma phieu: " << slipid
        << " | Doc gia: " << readerID
        << " | Ma sach: " << bookID
        << " | Ten sach: " << bookTitle
        << " | Tinh trang: " << bookCondition
        << " | Ngay muon: " << borrowStr
        << " | Han tra: " << dueStr;

    if (returned) {
        localtime_s(&timeInfo, &returnDate);
        strftime(returnStr, 20, "%d/%m/%Y", &timeInfo);
        cout << " | Ngay tra: " << returnStr;
    }
    else {
        cout << " | Chua tra";
        if (isOverdue()) {
            cout << " (Qua han " << getOverdueDays() << " ngay)";
        }
    }
    cout << endl;
}

string BorrowSlip::toString() const {
    stringstream ss;
    ss << slipid << ";" << readerID << ";" << bookID << ";" << bookTitle << ";" 
       << bookCondition << ";" << borrowDate << ";" << dueDate << ";" 
       << returnDate << ";" << (returned ? "1" : "0");
    return ss.str();
}

BorrowSlip BorrowSlip::fromString(const string& line) {
    stringstream ss(line);
    string sid, rid, bid, title, condition, borrowStr, dueStr, returnStr, returnedStr;
    getline(ss, sid, ';');
    getline(ss, rid, ';');
    getline(ss, bid, ';');
    getline(ss, title, ';');
    getline(ss, condition, ';');
    getline(ss, borrowStr, ';');
    getline(ss, dueStr, ';');
    getline(ss, returnStr, ';');
    getline(ss, returnedStr, ';');

    BorrowSlip slip(sid, rid, bid, title, condition);

    // Khoi phuc cac ngay tu file
    if (!borrowStr.empty()) {
        slip.setBorrowDate(static_cast<time_t>(stoll(borrowStr)));
    }
    if (!dueStr.empty()) {
        slip.setDueDate(static_cast<time_t>(stoll(dueStr)));
    }
    if (!returnStr.empty()) {
        slip.setReturnDate(static_cast<time_t>(stoll(returnStr)));
    }
    if (!returnedStr.empty()) {
        slip.setReturned(returnedStr == "1");
    }

    return slip;
}
