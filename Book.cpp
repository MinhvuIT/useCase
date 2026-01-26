#include "Book.h"
#include <sstream>
#include <iostream>
using namespace std;

Book::Book(string id, string t, string a, string p, int y, string c)
    : bookid(id), title(t), author(a), publisher(p), publishYear(y), category(c), status(BookStatus::AVAILABLE) {
}

void Book::display() const {
    cout << "Ma sach: " << bookid 
         << " | Ten: " << title 
         << " | Tac gia: " << author 
         << " | Nam XB: " << publishYear 
         << " | Trang thai: " << (status == BookStatus::AVAILABLE ? "Co san" : "Dang muon") << endl;
}

string Book::toString() const {
    return bookid + ";" + title + ";" + author + ";" + publisher + ";" + to_string(publishYear) + ";" + category;
}

string Book::getTitle() const {
    return title;
}

string Book::getID() const {
    return bookid;
}

string Book::getAuthor() const {
    return author;
}

string Book::getPublisher() const {
    return publisher;
}

int Book::getPublishYear() const {
    return publishYear;
}

string Book::getCategory() const {
    return category;
}

Book Book::fromString(const string& line) {
    stringstream ss(line);
    string id, t, a, p, yStr, c;
    getline(ss, id, ';');
    getline(ss, t, ';');
    getline(ss, a, ';');
    getline(ss, p, ';');
    getline(ss, yStr, ';');
    getline(ss, c, ';');
    return Book(id, t, a, p, stoi(yStr), c);
}

bool Book::updateStatus(BookStatus newStatus) {
    status = newStatus;
    return true;
}

BookStatus Book::getStatus() const {
    return status;
}
