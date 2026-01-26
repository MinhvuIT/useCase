#include "LibrarySystem.h"
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

Library::Library() {
    // Constructor
}

Library::~Library() {
    for (auto u : users) {
        delete u;
    }
    users.clear();
}

bool Library::registerUser(User* u) {
    // Kiem tra user da ton tai chua
    for (const auto& user : users) {
        if (user->getEmail() == u->getEmail()) {
            cout << "Email da duoc dang ky!" << endl;
            return false;
        }
    }
    users.push_back(u);
    cout << "Dang ky thanh cong: " << u->getName() << endl;
    return true;
}

User* Library::login(const string& email, const string& pass) {
    for (auto& u : users) {
        if (u->login(email, pass)) {
            cout << "Dang nhap thanh cong: " << u->getName() << endl;
            return u;
        }
    }
    cout << "Dang nhap that bai! Email hoac mat khau khong dung." << endl;
    return nullptr;
}

void Library::logout(User* u) {
    if (u) {
        u->logout();
    }
}

User* Library::findUserByEmail(const string& email) {
    for (auto& u : users) {
        if (u->getEmail() == email) {
            return u;
        }
    }
    return nullptr;
}

void Library::addBook(const Book& b) {
    // Kiem tra sach da ton tai chua
    for (const auto& book : books) {
        if (book.getID() == b.getID()) {
            cout << "Sach voi ma " << b.getID() << " da ton tai!" << endl;
            return;
        }
    }
    books.push_back(b);
    cout << "Them sach thanh cong: " << b.getTitle() << endl;
}

bool Library::removeBook(const string& bookID) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->getID() == bookID) {
            if (it->getStatus() == BookStatus::BORROWED) {
                cout << "Khong the xoa sach dang duoc muon!" << endl;
                return false;
            }
            cout << "Xoa sach thanh cong: " << it->getTitle() << endl;
            books.erase(it);
            return true;
        }
    }
    cout << "Khong tim thay sach voi ma: " << bookID << endl;
    return false;
}

void Library::searchBook(const string& keyword) const {
    cout << "\n===== KET QUA TIM KIEM: " << keyword << " =====" << endl;
    int found = 0;
    for (const auto& b : books) {
        if (b.getTitle().find(keyword) != string::npos ||
            b.getAuthor().find(keyword) != string::npos ||
            b.getCategory().find(keyword) != string::npos ||
            b.getID().find(keyword) != string::npos) {
            b.display();
            found++;
        }
    }
    if (found == 0) {
        cout << "Khong tim thay sach nao." << endl;
    }
    cout << "Tim thay " << found << " ket qua." << endl;
}

Book* Library::findBookByID(const string& bookID) {
    for (auto& b : books) {
        if (b.getID() == bookID) {
            return &b;
        }
    }
    return nullptr;
}

void Library::displayAllBooks() const {
    cout << "\n===== DANH SACH SACH =====" << endl;
    if (books.empty()) {
        cout << "Thu vien chua co sach nao." << endl;
    } else {
        for (const auto& b : books) {
            b.display();
        }
    }
    cout << "Tong: " << books.size() << " quyen sach." << endl;
}

bool Library::borrowBook(User& u, const string& bookID) {
    // Kiem tra gioi han muon sach (toi da 3 quyen)
    int currentBorrowCount = 0;
    for (const auto& record : borrowRecords) {
        if (record.getReaderID() == u.getEmail() && !record.isReturned()) {
            currentBorrowCount++;
        }
    }
    
    if (currentBorrowCount >= 3) {
        cout << "Ban da muon toi da 3 quyen sach. Vui long tra sach truoc khi muon them." << endl;
        return false;
    }
    
    // Tim sach
    for (auto& b : books) {
        if (b.getID() == bookID) {
            if (b.getStatus() != BookStatus::AVAILABLE) {
                cout << "Sach hien khong co san!" << endl;
                return false;
            }
            
            // Cap nhat trang thai sach
            b.updateStatus(BookStatus::BORROWED);
            
            // Tao phieu muon
            string slipID = "SLIP" + to_string(time(0));
            BorrowSlip slip(slipID, u.getEmail(), bookID, b.getTitle(), "Tot");
            borrowRecords.push_back(slip);
            report.addBorrowSlip(slip);
            
            cout << u.getName() << " da muon sach: " << b.getTitle() << endl;
            return true;
        }
    }
    
    cout << "Khong tim thay sach voi ma: " << bookID << endl;
    return false;
}

bool Library::returnBook(User& u, const string& bookID, const string& condition) {
    for (auto& r : borrowRecords) {
        if (r.getBookID() == bookID && r.getReaderID() == u.getEmail() && !r.isReturned()) {
            r.markReturned();
            
            // Cap nhat trang thai sach
            for (auto& b : books) {
                if (b.getID() == bookID) {
                    b.updateStatus(BookStatus::AVAILABLE);
                    break;
                }
            }
            
            // Kiem tra qua han va tao phieu phat
            if (r.isOverdue()) {
                int overdueDays = r.getOverdueDays();
                createFine(u.getEmail(), bookID, "Qua han", overdueDays);
            }
            
            // Kiem tra tinh trang sach
            if (condition == "Hu hong" || condition == "Damaged") {
                createFine(u.getEmail(), bookID, "Hu hong", 0);
            } else if (condition == "Mat" || condition == "Lost") {
                createFine(u.getEmail(), bookID, "Mat sach", 0);
            }
            
            cout << u.getName() << " da tra sach: " << bookID << endl;
            return true;
        }
    }
    
    cout << "Khong tim thay phieu muon cho sach: " << bookID << endl;
    return false;
}

void Library::showHistory(const User& u) const {
    cout << "\n===== LICH SU MUON TRA CUA " << u.getName() << " =====" << endl;
    int count = 0;
    for (const auto& r : borrowRecords) {
        if (r.getReaderID() == u.getEmail()) {
            r.display();
            count++;
        }
    }
    if (count == 0) {
        cout << "Chua co lich su muon sach." << endl;
    }
}

void Library::createFine(const string& readerID, const string& bookID, const string& reason, int overdueDays) {
    string fineID = "FINE" + to_string(time(0));
    Fine fine(fineID, readerID, bookID, reason, overdueDays);
    fines.push_back(fine);
    report.addFine(fine);
    fine.display();
}

void Library::generateReport() {
    report.generateFineRevenueReport();
}

void Library::listBorrowedBooks() const {
    cout << "\n===== DANH SACH SACH DANG MUON =====" << endl;
    int count = 0;
    for (const auto& r : borrowRecords) {
        if (!r.isReturned()) {
            r.display();
            count++;
        }
    }
    if (count == 0) {
        cout << "Khong co sach nao dang duoc muon." << endl;
    }
    cout << "Tong: " << count << " quyen." << endl;
}

void Library::listOverdueReaders() const {
    cout << "\n===== DANH SACH DOC GIA QUA HAN =====" << endl;
    int count = 0;
    for (const auto& r : borrowRecords) {
        if (!r.isReturned() && r.isOverdue()) {
            cout << "Doc gia: " << r.getReaderID()
                 << " | Sach: " << r.getBookTitle()
                 << " | Qua han: " << r.getOverdueDays() << " ngay" << endl;
            count++;
        }
    }
    if (count == 0) {
        cout << "Khong co doc gia nao qua han." << endl;
    }
}

void Library::saveBooks(const string& filename) const {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Loi: Khong the mo file " << filename << endl;
        return;
    }
    
    // Ghi header
    fout << "# Danh sach sach thu vien" << endl;
    fout << "# Format: MaSach;TenSach;TacGia;NhaXuatBan;NamXB;TheLoai;TrangThai" << endl;
    fout << "# TrangThai: 0 = Co san, 1 = Dang muon" << endl;
    fout << "#============================================" << endl;
    
    for (const auto& b : books) {
        // Ghi them trang thai sach
        fout << b.toString() << ";" << static_cast<int>(b.getStatus()) << endl;
    }
    fout.close();
    cout << "Da luu " << books.size() << " sach vao file: " << filename << endl;
}

void Library::loadBooks(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        // File chua ton tai - khong bao loi, se tao moi khi luu
        cout << "File " << filename << " chua ton tai. Se tao moi khi luu." << endl;
        return;
    }
    
    books.clear(); // Xoa danh sach cu truoc khi load
    string line;
    int count = 0;
    
    while (getline(fin, line)) {
        // Bo qua dong comment va dong trong
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        try {
            // Parse line: MaSach;TenSach;TacGia;NhaXuatBan;NamXB;TheLoai;TrangThai
            stringstream ss(line);
            string id, title, author, publisher, yearStr, category, statusStr;
            
            getline(ss, id, ';');
            getline(ss, title, ';');
            getline(ss, author, ';');
            getline(ss, publisher, ';');
            getline(ss, yearStr, ';');
            getline(ss, category, ';');
            getline(ss, statusStr, ';');
            
            if (!id.empty() && !title.empty()) {
                Book book(id, title, author, publisher, stoi(yearStr), category);
                
                // Doc trang thai sach neu co
                if (!statusStr.empty()) {
                    int status = stoi(statusStr);
                    if (status == 1) {
                        book.updateStatus(BookStatus::BORROWED);
                    }
                }
                
                books.push_back(book);
                count++;
            }
        } catch (const exception& e) {
            cerr << "Loi doc dong: " << line << endl;
        }
    }
    
    fin.close();
    cout << "Da tai " << count << " sach tu file: " << filename << endl;
}

void Library::saveBorrowRecords(const string& filename) const {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Loi: Khong the mo file " << filename << endl;
        return;
    }

    // Ghi header
    fout << "# Danh sach phieu muon sach" << endl;
    fout << "# Format: MaPhieu;EmailDocGia;MaSach;TenSach;TinhTrang;NgayMuon;HanTra;NgayTra;DaTra" << endl;
    fout << "# DaTra: 0 = Chua tra, 1 = Da tra" << endl;
    fout << "#============================================" << endl;

    for (const auto& slip : borrowRecords) {
        fout << slip.toString() << endl;
    }

    fout.close();
    cout << "Da luu " << borrowRecords.size() << " phieu muon vao file: " << filename << endl;
}

void Library::loadBorrowRecords(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "File " << filename << " chua ton tai. Se tao moi khi luu." << endl;
        return;
    }

    borrowRecords.clear();
    string line;
    int count = 0;

    while (getline(fin, line)) {
        // Bo qua dong comment va dong trong
        if (line.empty() || line[0] == '#') {
            continue;
        }

        try {
            BorrowSlip slip = BorrowSlip::fromString(line);
            if (!slip.getSlipID().empty()) {
                borrowRecords.push_back(slip);
                report.addBorrowSlip(slip);
                count++;
            }
        }
        catch (const exception& e) {
            cerr << "Loi doc dong: " << line << endl;
        }
    }

    fin.close();
    cout << "Da tai " << count << " phieu muon tu file: " << filename << endl;
}

void Library::saveUsers(const string& filename) const {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Loi: Khong the mo file " << filename << endl;
        return;
    }
    // Simplified - in production, you'd serialize user data properly
    fout.close();
}

void Library::loadUsers(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Loi: Khong the mo file " << filename << endl;
        return;
    }
    // Simplified - in production, you'd deserialize user data properly
    fin.close();
}

vector<Book>& Library::getBooks() {
    return books;
}

vector<User*>& Library::getUsers() {
    return users;
}

int Library::getBookCount() const {
    return static_cast<int>(books.size());
}

int Library::getUserCount() const {
    return static_cast<int>(users.size());
}
