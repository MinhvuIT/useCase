#ifndef REPORT_H
#define REPORT_H
#include <string>
#include <vector>
#include "Fine.h"
#include "BorrowSlip.h"
using namespace std;

class Report {
private:
    vector<Fine> fines;
    vector<BorrowSlip> borrowSlips;

public:
    // Fine management
    void addFine(const Fine& f);
    void addBorrowSlip(const BorrowSlip& slip);
    
    // Reports theo class diagram
    bool generateFineRevenueReport() const;
    
    // Danh sach sach dang muon
    void listBorrowedBooks() const;
    
    // Danh sach doc gia qua han
    void listOverdueReaders() const;
    
    // Thong ke doanh thu theo thang/quy
    double calculateMonthlyRevenue(int month, int year) const;
    double calculateQuarterlyRevenue(int quarter, int year) const;
    
    // File operations
    void saveReport(const string& filename = "report.txt") const;
    void loadReport(const string& filename = "report.txt");
    
    // Getters
    double getTotalFineAmount() const;
    int getTotalFineCount() const;
};

#endif
