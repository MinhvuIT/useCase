#include "LibrarySystem.h"
#include "Reader.h"
#include "Admin.h"
#include "Book.h"
#include <iostream>
#include <limits>
using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void readerMenu(Library& lib, User* u) {
    int choice;
    do {
        cout << "\n========== MENU DOC GIA ==========" << endl;
        cout << "1. Tim kiem sach" << endl;
        cout << "2. Muon sach" << endl;
        cout << "3. Tra sach" << endl;
        cout << "4. Xem lich su muon tra" << endl;
        cout << "5. Cap nhat thong tin ca nhan" << endl;
        cout << "0. Dang xuat" << endl;
        cout << "Lua chon: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string keyword;
            cout << "Nhap tu khoa tim kiem: ";
            clearInput();
            getline(cin, keyword);
            lib.searchBook(keyword);
            break;
        }
        case 2: {
            lib.displayAllBooks();
            string bookID;
            cout << "Nhap ma sach can muon: ";
            cin >> bookID;
            lib.borrowBook(*u, bookID);
            break;
        }
        case 3: {
            lib.showHistory(*u);
            string bookID;
            cout << "Nhap ma sach can tra: ";
            cin >> bookID;

            cout << "Tinh trang sach (Tot/Hu hong/Mat): ";
            string condition;
            cin >> condition;

            lib.returnBook(*u, bookID, condition);
            break;
        }
        case 4:
            lib.showHistory(*u);
            break;
        case 5: {
            string name, pass;
            cout << "Nhap ten moi: ";
            clearInput();
            getline(cin, name);
            cout << "Nhap mat khau moi: ";
            cin >> pass;
            u->updateProfile(name, pass);
            cout << "Cap nhat thong tin thanh cong!" << endl;
            break;
        }
        case 0:
            lib.logout(u);
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
        }
    } while (choice != 0);
}

void adminMenu(Library& lib, User* u) {
    int choice;
    do {
        cout << "\n========== MENU QUAN TRI ==========" << endl;
        cout << "=== QUAN LY SACH ===" << endl;
        cout << "1. Them sach moi" << endl;
        cout << "2. Tim kiem sach" << endl;
        cout << "3. Hien thi tat ca sach" << endl;
        cout << "4. Xoa sach" << endl;
        cout << "=== QUAN LY DOC GIA ===" << endl;
        cout << "5. Dang ky doc gia moi" << endl;
        cout << "6. Xem danh sach doc gia" << endl;
        cout << "=== QUAN LY MUON TRA ===" << endl;
        cout << "7. Lap phieu muon cho doc gia" << endl;
        cout << "8. Xu ly tra sach" << endl;
        cout << "9. Xem lich su muon tra cua doc gia" << endl;
        cout << "10. Tao phieu phat" << endl;
        cout << "=== BAO CAO & THONG KE ===" << endl;
        cout << "11. Danh sach sach dang muon" << endl;
        cout << "12. Danh sach doc gia qua han" << endl;
        cout << "13. Bao cao doanh thu phat" << endl;
        cout << "=== LUU TRU DU LIEU ===" << endl;
        cout << "14. Luu danh sach sach vao file" << endl;
        cout << "15. Tai danh sach sach tu file" << endl;
        cout << "16. Luu danh sach phieu muon vao file" << endl;
        cout << "17. Tai danh sach phieu muon tu file" << endl;
        cout << "0. Dang xuat" << endl;
        cout << "Lua chon: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string id, title, author, publisher, category;
            int year;
            cout << "Nhap ma sach: "; cin >> id;
            cout << "Nhap ten sach: "; clearInput(); getline(cin, title);
            cout << "Nhap tac gia: "; getline(cin, author);
            cout << "Nhap nha xuat ban: "; getline(cin, publisher);
            cout << "Nhap nam xuat ban: "; cin >> year;
            cout << "Nhap the loai: "; cin >> category;
            lib.addBook(Book(id, title, author, publisher, year, category));
            break;
        }
        case 2: {
            string keyword;
            cout << "Nhap tu khoa tim kiem: ";
            clearInput();
            getline(cin, keyword);
            lib.searchBook(keyword);
            break;
        }
        case 3:
            lib.displayAllBooks();
            break;
        case 4: {
            lib.displayAllBooks();
            string bookID;
            cout << "Nhap ma sach can xoa: ";
            cin >> bookID;
            lib.removeBook(bookID);
            break;
        }
        case 5: {
            string id, name, email, pass, dob;
            int typeChoice;
            cout << "Nhap ma doc gia: "; cin >> id;
            cout << "Nhap ho ten: "; clearInput(); getline(cin, name);
            cout << "Nhap email: "; cin >> email;
            cout << "Nhap mat khau: "; cin >> pass;
            cout << "Nhap ngay sinh (dd/mm/yyyy): "; cin >> dob;
            cout << "Loai doc gia (1. Sinh vien, 2. Giao vien): "; cin >> typeChoice;

            ReaderType type = (typeChoice == 2) ? ReaderType::TEACHER : ReaderType::STUDENT;
            Reader* r = new Reader(id, name, email, pass, dob, type);
            lib.registerUser(r);
            break;
        }
        case 6: {
            cout << "\n===== DANH SACH DOC GIA =====" << endl;
            for (auto& user : lib.getUsers()) {
                if (!user->isAdmin()) {
                    cout << "Ten: " << user->getName()
                        << " | Email: " << user->getEmail() << endl;
                }
            }
            break;
        }
        case 7: {
            string email, bookID;
            cout << "Nhap email doc gia: "; cin >> email;

            User* reader = lib.findUserByEmail(email);
            if (reader) {
                lib.displayAllBooks();
                cout << "Nhap ma sach can muon: "; cin >> bookID;
                lib.borrowBook(*reader, bookID);
            }
            else {
                cout << "Khong tim thay doc gia voi email: " << email << endl;
            }
            break;
        }
        case 8: {
            string email, bookID, condition;
            cout << "Nhap email doc gia: "; cin >> email;

            User* reader = lib.findUserByEmail(email);
            if (reader) {
                lib.showHistory(*reader);
                cout << "Nhap ma sach can tra: "; cin >> bookID;
                cout << "Tinh trang sach (Tot/Hu hong/Mat): "; cin >> condition;
                lib.returnBook(*reader, bookID, condition);
            }
            else {
                cout << "Khong tim thay doc gia voi email: " << email << endl;
            }
            break;
        }
        case 9: {
            string email;
            cout << "Nhap email doc gia: "; cin >> email;
            User* reader = lib.findUserByEmail(email);
            if (reader) {
                lib.showHistory(*reader);
            }
            else {
                cout << "Khong tim thay doc gia voi email: " << email << endl;
            }
            break;
        }
        case 10: {
            string email, bookID, reason;
            int overdueDays = 0;
            cout << "Nhap email doc gia: "; cin >> email;
            cout << "Nhap ma sach: "; cin >> bookID;
            cout << "Ly do phat (Qua han/Hu hong/Mat sach): ";
            clearInput();
            getline(cin, reason);

            if (reason == "Qua han" || reason == "Overdue") {
                cout << "So ngay qua han: "; cin >> overdueDays;
            }

            lib.createFine(email, bookID, reason, overdueDays);
            break;
        }
        case 11:
            lib.listBorrowedBooks();
            break;
        case 12:
            lib.listOverdueReaders();
            break;
        case 13:
            lib.generateReport();
            break;
        case 14: {
            string filename;
            cout << "Nhap ten file (Enter de dung mac dinh 'book.txt'): ";
            clearInput();
            getline(cin, filename);
            if (filename.empty()) {
                filename = "book.txt";
            }
            lib.saveBooks(filename);
            break;
        }
        case 15: {
            string filename;
            cout << "Nhap ten file (Enter de dung mac dinh 'book.txt'): ";
            clearInput();
            getline(cin, filename);
            if (filename.empty()) {
                filename = "book.txt";
            }
            lib.loadBooks(filename);
            break;
        }
        case 16: {
            string filename;
            cout << "Nhap ten file (Enter de dung mac dinh 'borrow.txt'): ";
            clearInput();
            getline(cin, filename);
            if (filename.empty()) {
                filename = "borrow.txt";
            }
            lib.saveBorrowRecords(filename);
            break;
        }
        case 17: {
            string filename;
            cout << "Nhap ten file (Enter de dung mac dinh 'borrow.txt'): ";
            clearInput();
            getline(cin, filename);
            if (filename.empty()) {
                filename = "borrow.txt";
            }
            lib.loadBorrowRecords(filename);
            break;
        }
        case 0:
            lib.logout(u);
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
        }
    } while (choice != 0);
}

void mainMenu(Library& lib) {
    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "   HE THONG QUAN LY THU VIEN" << endl;
        cout << "========================================" << endl;
        cout << "1. Dang nhap" << endl;
        cout << "2. Dang ky tai khoan doc gia" << endl;
        cout << "0. Thoat" << endl;
        cout << "Lua chon: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string email, pass;
            cout << "Nhap email: ";
            cin >> email;
            cout << "Nhap mat khau: ";
            cin >> pass;

            User* u = lib.login(email, pass);
            if (u) {
                if (u->isAdmin()) {
                    adminMenu(lib, u);
                }
                else {
                    readerMenu(lib, u);
                }
            }
            break;
        }
        case 2: {
            string id, name, email, pass, dob;
            int typeChoice;
            cout << "=== DANG KY TAI KHOAN DOC GIA ===" << endl;
            cout << "Nhap ma doc gia: "; cin >> id;
            cout << "Nhap ho ten: "; clearInput(); getline(cin, name);
            cout << "Nhap email: "; cin >> email;
            cout << "Nhap mat khau: "; cin >> pass;
            cout << "Nhap ngay sinh (dd/mm/yyyy): "; cin >> dob;
            cout << "Loai doc gia (1. Sinh vien, 2. Giao vien): "; cin >> typeChoice;

            ReaderType type = (typeChoice == 2) ? ReaderType::TEACHER : ReaderType::STUDENT;
            Reader* r = new Reader(id, name, email, pass, dob, type);
            lib.registerUser(r);
            break;
        }
        case 0:
            cout << "Cam on ban da su dung he thong!" << endl;
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
        }
    } while (choice != 0);
}

void initSampleBooks(Library& lib) {
    // Them sach mau neu chua co sach nao
    if (lib.getBookCount() == 0) {
        cout << "\nKhong tim thay file sach. Them sach mau..." << endl;
        lib.addBook(Book("B001", "Lap trinh C++", "Bjarne Stroustrup", "Pearson", 2013, "CNTT"));
        lib.addBook(Book("B002", "Cong nghe phan mem", "Ian Sommerville", "Pearson", 2015, "CNTT"));
        lib.addBook(Book("B003", "Cau truc du lieu va giai thuat", "Thomas Cormen", "MIT Press", 2009, "CNTT"));
        lib.addBook(Book("B004", "He dieu hanh", "Andrew Tanenbaum", "Pearson", 2014, "CNTT"));
        lib.addBook(Book("B005", "Mang may tinh", "Andrew Tanenbaum", "Pearson", 2011, "CNTT"));
    }
}

int main() {
    Library lib;

    cout << "\n========================================" << endl;
    cout << "   CHAO MUNG DEN VOI HE THONG THU VIEN" << endl;
    cout << "========================================" << endl;

    // Tao san mot Admin
    Admin* admin = new Admin("AD001", "Quan Tri Vien", "admin@library.com", "admin", "01/01/1990", 1);
    lib.registerUser(admin);

    // Tao san mot doc gia mau
    Reader* r1 = new Reader("R001", "Nguyen Van A", "a@gmail.com", "123", "15/05/2000", ReaderType::STUDENT);
    lib.registerUser(r1);

    // Tai danh sach sach tu file
    cout << "\n--- Dang tai du lieu tu file ---" << endl;
    lib.loadBooks("book.txt");

    // Neu khong co sach, them sach mau
    initSampleBooks(lib);

    // Tai danh sach phieu muon tu file
    lib.loadBorrowRecords("borrow.txt");

    cout << "\n========================================" << endl;
    cout << "   TAI KHOAN MAC DINH" << endl;
    cout << "========================================" << endl;
    cout << "- Admin: admin@library.com / admin" << endl;
    cout << "- Doc gia: a@gmail.com / 123" << endl;

    // Chay menu chinh
    mainMenu(lib);

    // Luu du lieu truoc khi thoat
    cout << "\n--- Dang luu du lieu vao file ---" << endl;
    lib.saveBooks("book.txt");
    lib.saveBorrowRecords("borrow.txt");

    cout << "He thong da dong. Hen gap lai!" << endl;

    return 0;
}
