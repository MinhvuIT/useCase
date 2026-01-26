#ifndef READER_H
#define READER_H
#include <string>
#include <vector>
#include <ctime>
#include "User.h"
#include "Book.h"
#include "BorrowSlip.h"
using namespace std;

// Enum ReaderType theo class diagram
enum class ReaderType {
    STUDENT,
    TEACHER
};

class Reader : public User {
private:
    string dateOfBirth;
    ReaderType readerType;
    vector<BorrowSlip> borrowHistory;
    static const int MAX_BOOKS = 3; // Gioi han muon toi da 3 quyen

public:
    Reader(string id, string name, string mail, string pass, string dob, ReaderType type = ReaderType::STUDENT);
    
    // Override methods
    bool isAdmin() const override;
    
    // Reader-specific methods theo class diagram
    vector<Book> searchBook(const string& keyword, const vector<Book>& allBooks) const;
    bool borrowBook(Book& book, const string& bookTitle);
    bool returnBook(const string& bookID);
    vector<BorrowSlip> viewBorrowHistory() const;
    
    // Getters
    string getDateOfBirth() const;
    ReaderType getReaderType() const;
    int getCurrentBorrowCount() const;
    bool canBorrowMore() const;
    
    // Setters
    void setDateOfBirth(const string& dob);
    void setReaderType(ReaderType type);
};

#endif
