#ifndef BORROWSLIPDETAIL_H
#define BORROWSLIPDETAIL_H
#include <string>
#include "Book.h"
using namespace std;

// BorrowSlipDetail - Chi tiet phieu muon (lien ket giua BorrowSlip va Book)
// Theo class diagram: quan he 0..* giua BorrowSlipDetail va Book
class BorrowSlipDetail {
private:
    string slipID;
    string bookID;
    int quantity;

public:
    BorrowSlipDetail(string sid = "", string bid = "", int qty = 1);
    
    // Getters
    string getSlipID() const;
    string getBookID() const;
    int getQuantity() const;
    
    // Setters
    void setQuantity(int qty);
    
    // Display
    void display() const;
};

#endif
