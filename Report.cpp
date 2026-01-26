#include "Report.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;

void Report::addFine(const Fine& f) {
    fines.push_back(f);
}

void Report::addBorrowSlip(const BorrowSlip& slip) {
    borrowSlips.push_back(slip);
}

bool Report::generateFineRevenueReport() const {
    double total = 0;
    int overdueCount = 0;
    int damagedCount = 0;
    int lostCount = 0;
    
    for (const auto& f : fines) {
        total += f.getAmount();
        if (f.getReason() == "Overdue" || f.getReason() == "Qua han") {
            overdueCount++;
        } else if (f.getReason() == "Damaged" || f.getReason() == "Hu hong") {
            damagedCount++;
        } else if (f.getReason() == "Lost" || f.getReason() == "Mat sach") {
            lostCount++;
        }
    }
    
    cout << "\n========== BAO CAO DOANH THU PHAT ==========" << endl;
    cout << "Tong so phieu phat: " << fines.size() << endl;
    cout << "  - Qua han: " << overdueCount << " phieu" << endl;
    cout << "  - Hu hong: " << damagedCount << " phieu" << endl;
    cout << "  - Mat sach: " << lostCount << " phieu" << endl;
    cout << "Tong doanh thu: " << total << " VND" << endl;
    cout << "=============================================" << endl;
    
    return true;
}

void Report::listBorrowedBooks() const {
    cout << "\n========== DANH SACH SACH DANG MUON ==========" << endl;
    int count = 0;
    for (const auto& slip : borrowSlips) {
        if (!slip.isReturned()) {
            slip.display();
            count++;
        }
    }
    if (count == 0) {
        cout << "Khong co sach nao dang duoc muon." << endl;
    }
    cout << "Tong: " << count << " quyen" << endl;
    cout << "==============================================" << endl;
}

void Report::listOverdueReaders() const {
    cout << "\n========== DANH SACH DOC GIA QUA HAN ==========" << endl;
    int count = 0;
    for (const auto& slip : borrowSlips) {
        if (!slip.isReturned() && slip.isOverdue()) {
            cout << "Doc gia: " << slip.getReaderID()
                 << " | Sach: " << slip.getBookTitle()
                 << " | Qua han: " << slip.getOverdueDays() << " ngay" << endl;
            count++;
        }
    }
    if (count == 0) {
        cout << "Khong co doc gia nao qua han." << endl;
    }
    cout << "Tong: " << count << " truong hop" << endl;
    cout << "===============================================" << endl;
}

double Report::calculateMonthlyRevenue(int month, int year) const {
    double total = 0;
    // Simplified - in production, you'd check fine creation dates
    for (const auto& f : fines) {
        total += f.getAmount();
    }
    return total;
}

double Report::calculateQuarterlyRevenue(int quarter, int year) const {
    double total = 0;
    // Simplified - in production, you'd check fine creation dates
    for (const auto& f : fines) {
        total += f.getAmount();
    }
    return total;
}

void Report::saveReport(const string& filename) const {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Loi: Khong the mo file " << filename << endl;
        return;
    }
    
    fout << "=== FINES ===" << endl;
    for (const auto& f : fines) {
        fout << f.toString() << endl;
    }
    
    fout << "=== BORROW SLIPS ===" << endl;
    for (const auto& slip : borrowSlips) {
        fout << slip.toString() << endl;
    }
    
    fout.close();
    cout << "Luu bao cao thanh cong: " << filename << endl;
}

void Report::loadReport(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Loi: Khong the mo file " << filename << endl;
        return;
    }
    
    string line;
    bool readingFines = false;
    bool readingSlips = false;
    
    while (getline(fin, line)) {
        if (line == "=== FINES ===") {
            readingFines = true;
            readingSlips = false;
            continue;
        }
        if (line == "=== BORROW SLIPS ===") {
            readingFines = false;
            readingSlips = true;
            continue;
        }
        
        if (readingFines && !line.empty()) {
            fines.push_back(Fine::fromString(line));
        } else if (readingSlips && !line.empty()) {
            borrowSlips.push_back(BorrowSlip::fromString(line));
        }
    }
    
    fin.close();
    cout << "Tai bao cao thanh cong: " << filename << endl;
}

double Report::getTotalFineAmount() const {
    double total = 0;
    for (const auto& f : fines) {
        total += f.getAmount();
    }
    return total;
}

int Report::getTotalFineCount() const {
    return static_cast<int>(fines.size());
}
