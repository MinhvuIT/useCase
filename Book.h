// ================= Book.h =================
#ifndef BOOK_H
#define BOOK_H
#include <string>
using namespace std;

// Khai bao enum BookStatus
enum class BookStatus {
    AVAILABLE,
    BORROWED
};

class Book {
private:
    string bookid;
    string title;
    string author;
    string publisher;
    int publishYear;
    string category;
    BookStatus status;

public:
    Book(string id = "", string t = "", string a = "", string p = "", int y = 0, string c = "");
    bool updateStatus(BookStatus newStatus);
    string getTitle() const;
    string getID() const;
    string getAuthor() const;
    string getPublisher() const;
    int getPublishYear() const;
    string getCategory() const;
    BookStatus getStatus() const;
    void display() const;
    string toString() const;
    static Book fromString(const string& line);
};
#endif
