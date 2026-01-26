#include "Admin.h"
#include "Report.h"
#include <iostream>
#include <algorithm>
using namespace std;

Admin::Admin(string id, string name, string mail, string pass, string dob, int level) 
    : Reader(id, name, mail, pass, dob, ReaderType::TEACHER), adminLevel(level) {
}

bool Admin::isAdmin() const {
    return true;
}

bool Admin::addBook(vector<Book>& books, const Book& b) {
    // Kiem tra sach da ton tai chua
    for (const auto& book : books) {
        if (book.getID() == b.getID()) {
            cout << "Sach voi ma " << b.getID() << " da ton tai!" << endl;
            return false;
        }
    }
    books.push_back(b);
    cout << "Them sach thanh cong: " << b.getTitle() << endl;
    return true;
}

bool Admin::updateBook(vector<Book>& books, const string& bookID, const Book& newInfo) {
    for (auto& book : books) {
        if (book.getID() == bookID) {
            book = newInfo;
            cout << "Cap nhat sach thanh cong: " << bookID << endl;
            return true;
        }
    }
    cout << "Khong tim thay sach voi ma: " << bookID << endl;
    return false;
}

bool Admin::deleteBook(vector<Book>& books, const string& bookID) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->getID() == bookID) {
            // Kiem tra sach co dang duoc muon khong
            if (it->getStatus() == BookStatus::BORROWED) {
                cout << "Khong the xoa sach dang duoc muon!" << endl;
                return false;
            }
            cout << "Xoa sach thanh cong: " << it->getTitle() << endl;
            books.erase(it);
            return true;
        }
    }
    cout << "Khong tim thay sach voi ma: " << bookID << endl;
    return false;
}

bool Admin::manageMember(vector<Reader*>& readers) {
    cout << "\n===== DANH SACH DOC GIA =====" << endl;
    if (readers.empty()) {
        cout << "Chua co doc gia nao." << endl;
    } else {
        for (const auto& reader : readers) {
            cout << "Ma: " << reader->getUserId()
                 << " | Ten: " << reader->getName()
                 << " | Email: " << reader->getEmail() << endl;
        }
    }
    return true;
}

bool Admin::addMember(vector<Reader*>& readers, Reader* newReader) {
    // Kiem tra doc gia da ton tai chua
    for (const auto& reader : readers) {
        if (reader->getEmail() == newReader->getEmail()) {
            cout << "Doc gia voi email " << newReader->getEmail() << " da ton tai!" << endl;
            return false;
        }
    }
    readers.push_back(newReader);
    cout << "Them doc gia thanh cong: " << newReader->getName() << endl;
    return true;
}

bool Admin::deleteMember(vector<Reader*>& readers, const string& readerID) {
    for (auto it = readers.begin(); it != readers.end(); ++it) {
        if ((*it)->getUserId() == readerID) {
            cout << "Xoa doc gia thanh cong: " << (*it)->getName() << endl;
            delete *it;
            readers.erase(it);
            return true;
        }
    }
    cout << "Khong tim thay doc gia voi ma: " << readerID << endl;
    return false;
}

Reader* Admin::findMember(vector<Reader*>& readers, const string& keyword) {
    for (auto& reader : readers) {
        if (reader->getUserId() == keyword || 
            reader->getName().find(keyword) != string::npos ||
            reader->getEmail() == keyword) {
            return reader;
        }
    }
    return nullptr;
}

BorrowSlip Admin::createBorrowSlip(const string& readerID, const string& bookID, 
                                    const string& bookTitle, const string& condition) {
    string slipID = "SLIP" + to_string(time(0));
    cout << "Tao phieu muon thanh cong: " << slipID << endl;
    return BorrowSlip(slipID, readerID, bookID, bookTitle, condition);
}

Fine Admin::createFine(const string& readerID, const string& bookID, 
                       const string& reason, int overdueDays) {
    string fineID = "FINE" + to_string(time(0));
    Fine fine(fineID, readerID, bookID, reason, overdueDays);
    cout << "Tao phieu phat thanh cong: " << fineID << " - So tien: " << fine.getAmount() << " VND" << endl;
    return fine;
}

bool Admin::generateReport(Report& report) {
    return report.generateFineRevenueReport();
}

int Admin::getAdminLevel() const {
    return adminLevel;
}
