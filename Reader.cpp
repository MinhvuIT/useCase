#include "Reader.h"
#include <iostream>
#include <algorithm>
using namespace std;

Reader::Reader(string id, string name, string email, string password, string dob, ReaderType type)
    : User(id, name, email, password), dateOfBirth(dob), readerType(type) {
}

bool Reader::isAdmin() const {
    return false;
}

vector<Book> Reader::searchBook(const string& keyword, const vector<Book>& allBooks) const {
    vector<Book> results;
    for (const auto& book : allBooks) {
        // Tim kiem theo ten sach, tac gia, the loai
        if (book.getTitle().find(keyword) != string::npos ||
            book.getAuthor().find(keyword) != string::npos ||
            book.getCategory().find(keyword) != string::npos) {
            results.push_back(book);
        }
    }
    return results;
}

bool Reader::borrowBook(Book& book, const string& bookTitle) {
    // Kiem tra dieu kien muon sach
    if (!canBorrowMore()) {
        cout << "Ban da muon toi da " << MAX_BOOKS << " quyen sach. Vui long tra sach truoc khi muon them." << endl;
        return false;
    }
    
    if (book.getStatus() != BookStatus::AVAILABLE) {
        cout << "Sach khong co san de muon." << endl;
        return false;
    }
    
    // Tao phieu muon
    string slipID = "SLIP" + to_string(time(0));
    BorrowSlip slip(slipID, userid, book.getID(), bookTitle, "Tot");
    borrowHistory.push_back(slip);
    
    // Cap nhat trang thai sach
    book.updateStatus(BookStatus::BORROWED);
    
    cout << "Muon sach thanh cong: " << bookTitle << endl;
    return true;
}

bool Reader::returnBook(const string& bookID) {
    for (auto& slip : borrowHistory) {
        if (slip.getBookID() == bookID && !slip.isReturned()) {
            slip.markReturned();
            
            // Kiem tra qua han
            if (slip.isOverdue()) {
                int overdueDays = slip.getOverdueDays();
                cout << "Sach tra tre " << overdueDays << " ngay. Vui long dong phat." << endl;
            }
            
            cout << "Tra sach thanh cong: " << bookID << endl;
            return true;
        }
    }
    
    cout << "Khong tim thay phieu muon cho sach: " << bookID << endl;
    return false;
}

vector<BorrowSlip> Reader::viewBorrowHistory() const {
    cout << "\n===== LICH SU MUON TRA SACH =====" << endl;
    if (borrowHistory.empty()) {
        cout << "Chua co lich su muon sach." << endl;
    } else {
        for (const auto& slip : borrowHistory) {
            slip.display();
        }
    }
    return borrowHistory;
}

string Reader::getDateOfBirth() const {
    return dateOfBirth;
}

ReaderType Reader::getReaderType() const {
    return readerType;
}

int Reader::getCurrentBorrowCount() const {
    int count = 0;
    for (const auto& slip : borrowHistory) {
        if (!slip.isReturned()) {
            count++;
        }
    }
    return count;
}

bool Reader::canBorrowMore() const {
    return getCurrentBorrowCount() < MAX_BOOKS;
}

void Reader::setDateOfBirth(const string& dob) {
    dateOfBirth = dob;
}

void Reader::setReaderType(ReaderType type) {
    readerType = type;
}
