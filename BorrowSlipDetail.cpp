#include "BorrowSlipDetail.h"
#include <iostream>
using namespace std;

BorrowSlipDetail::BorrowSlipDetail(string sid, string bid, int qty)
    : slipID(sid), bookID(bid), quantity(qty) {
}

string BorrowSlipDetail::getSlipID() const {
    return slipID;
}

string BorrowSlipDetail::getBookID() const {
    return bookID;
}

int BorrowSlipDetail::getQuantity() const {
    return quantity;
}

void BorrowSlipDetail::setQuantity(int qty) {
    quantity = qty;
}

void BorrowSlipDetail::display() const {
    cout << "Ma phieu: " << slipID 
         << " | Ma sach: " << bookID 
         << " | So luong: " << quantity << endl;
}
