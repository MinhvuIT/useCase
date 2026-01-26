// ================= LibrarySystem.h =================
#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H
#include <vector>
#include <string>
#include <fstream>
#include "User.h"
#include "Reader.h"
#include "Admin.h"
#include "Book.h"
#include "BorrowSlip.h"
#include "Fine.h"
#include "Report.h"
using namespace std;

class Library {
private:
    vector<User*> users;
    vector<Book> books;
    vector<BorrowSlip> borrowRecords;
    vector<Fine> fines;
    Report report;

public:
    Library();
    ~Library();
    
    // User management
    bool registerUser(User* u);
    User* login(const string& email, const string& pass);
    void logout(User* u);
    User* findUserByEmail(const string& email);
    
    // Book management
    void addBook(const Book& b);
    bool removeBook(const string& bookID);
    void searchBook(const string& keyword) const;
    Book* findBookByID(const string& bookID);
    void displayAllBooks() const;
    
    // Borrow/Return operations
    bool borrowBook(User& u, const string& bookID);
    bool returnBook(User& u, const string& bookID, const string& condition = "Tot");
    void showHistory(const User& u) const;
    
    // Fine management
    void createFine(const string& readerID, const string& bookID, const string& reason, int overdueDays);
    
    // Reports
    void generateReport();
    void listBorrowedBooks() const;
    void listOverdueReaders() const;
    
    // Data persistence
    void saveBooks(const string& filename = "books.txt") const;
    void loadBooks(const string& filename = "books.txt");
    void saveBorrowRecords(const string& filename = "borrows.txt") const;
    void loadBorrowRecords(const string& filename = "borrows.txt");
    void saveUsers(const string& filename = "users.txt") const;
    void loadUsers(const string& filename = "users.txt");
    
    // Getters
    vector<Book>& getBooks();
    vector<User*>& getUsers();
    int getBookCount() const;
    int getUserCount() const;
};

#endif
