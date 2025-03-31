#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
using namespace std;

class Password {
    string code;
public:
    void setPassword();
    bool verifyPassword(string);
};

void Password::setPassword() {
    cout << "Library Management System\n";
    cout << "\nSet a Password: ";
    code.clear();
    char ch;
    while ((ch = _getch()) != 13) {
        if (ch == 8 && !code.empty()) {  // Handle backspace
            cout << "\b \b";
            if (!code.empty()) code.erase(code.length() - 1, 1);
        } else if (ch != 8) {
            cout << "*";
            code.push_back(ch);
        }
    }
}

bool Password::verifyPassword(string pass) {
    return (pass == code);
}

class Book {
    string id, title, author;
public:
    void addBook();
    void displayBooks();
    void deleteBook(string);
};

void Book::addBook() {
    ofstream file("books.txt", ios::app);
    cout << "\nEnter Book ID: "; cin >> id;
    cout << "Enter Book Title: "; cin.ignore(); getline(cin, title);
    cout << "Enter Author Name: "; getline(cin, author);
    file << id << "|" << title << "|" << author << "\n";
    file.close();
    cout << "Book Added Successfully!\n";
}

void Book::displayBooks() {
    ifstream file("books.txt");
    if (!file) {
        cout << "No books available!\n";
        return;
    }
    cout << "\nBook List:\n";
    string record;
    while (getline(file, record)) {
        size_t pos1 = record.find('|');
        size_t pos2 = record.rfind('|');
        cout << "ID: " << record.substr(0, pos1) << " | Title: " << record.substr(pos1+1, pos2-pos1-1) << " | Author: " << record.substr(pos2+1) << "\n";
    }
    file.close();
}

void Book::deleteBook(string bookID) {
    ifstream file("books.txt");
    ofstream temp("temp.txt");
    string record;
    bool found = false;
    while (getline(file, record)) {
        if (record.substr(0, record.find('|')) != bookID) {
            temp << record << "\n";
        } else {
            found = true;
        }
    }
    file.close();
    temp.close();
    remove("books.txt");
    rename("temp.txt", "books.txt");
    if (found)
        cout << "Book Deleted Successfully!\n";
    else
        cout << "Book Not Found!\n";
}

int main() {
    Password p;
    Book b;
    int choice;
    string pass, bookID;

    p.setPassword();
    system("CLS");

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n2. Display Books\n3. Delete Book\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                b.addBook();
                break;
            case 2:
                b.displayBooks();
                break;
            case 3:
                cout << "Enter Book ID to Delete: "; cin >> bookID;
                b.deleteBook(bookID);
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid Choice!\n";
        }
    }
    return 0;
}
