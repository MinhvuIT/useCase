#ifndef ADMIN_H
#define ADMIN_H
#include <string>
#include <vector>
#include "Reader.h"
#include "Book.h"
#include "BorrowSlip.h"
#include "Fine.h"
using namespace std;

// Forward declaration
class Report;

class Admin : public Reader {
private:
    int adminLevel;

public:
    Admin(string id, string name, string mail, string pass, string dob, int level = 1);
    
    // Override
    bool isAdmin() const override;
    
    // Admin-specific methods theo class diagram
    bool addBook(vector<Book>& books, const Book& b);
    bool updateBook(vector<Book>& books, const string& bookID, const Book& newInfo);
    bool deleteBook(vector<Book>& books, const string& bookID);
    
    // User management
    bool manageMember(vector<Reader*>& readers);
    bool addMember(vector<Reader*>& readers, Reader* newReader);
    bool deleteMember(vector<Reader*>& readers, const string& readerID);
    Reader* findMember(vector<Reader*>& readers, const string& keyword);
    
    // Borrow/Return management
    BorrowSlip createBorrowSlip(const string& readerID, const string& bookID, 
                                 const string& bookTitle, const string& condition);
    Fine createFine(const string& readerID, const string& bookID, 
                    const string& reason, int overdueDays);
    
    // Report
    bool generateReport(class Report& report);
    
    // Getters
    int getAdminLevel() const;
};

#endif
