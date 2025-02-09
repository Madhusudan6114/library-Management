#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class Book {
public:
    int id;
    string title, author;
    bool isIssued;

    Book(int id, string title, string author) : id(id), title(title), author(author), isIssued(false) {}
};

class Library {
private:
    vector<Book> books;
    const string filename = "library_data.txt";

    void loadBooks() {
        ifstream file(filename);
        if (!file) return;
        books.clear();
        int id; string title, author; bool isIssued;
        while (file >> id >> ws && getline(file, title) && getline(file, author) && file >> isIssued) {
            books.push_back(Book(id, title, author));
            books.back().isIssued = isIssued;
        }
        file.close();
    }

    void saveBooks() {
        ofstream file(filename);
        for (const auto& book : books)
            file << book.id << "\n" << book.title << "\n" << book.author << "\n" << book.isIssued << "\n";
        file.close();
    }

public:
    Library() { loadBooks(); }

    void addBook(int id, string title, string author) {
        books.push_back(Book(id, title, author));
        saveBooks();
        cout << "Book added successfully!\n";
    }

    void issueBook(int id) {
        for (auto& book : books) {
            if (book.id == id && !book.isIssued) {
                book.isIssued = true;
                saveBooks();
                cout << "Book issued successfully!\n";
                return;
            }
        }
        cout << "Book not found or already issued!\n";
    }

    void returnBook(int id) {
        for (auto& book : books) {
            if (book.id == id && book.isIssued) {
                book.isIssued = false;
                saveBooks();
                cout << "Book returned successfully!\n";
                return;
            }
        }
        cout << "Book not found or not issued!\n";
    }

    void displayBooks() {
        cout << "\nLibrary Books:\n";
        cout << left << setw(5) << "ID" << setw(30) << "Title" << setw(20) << "Author" << "Status" << endl;
        cout << string(60, '-') << endl;
        for (const auto& book : books) {
            cout << left << setw(5) << book.id << setw(30) << book.title << setw(20) << book.author 
                 << (book.isIssued ? "Issued" : "Available") << endl;
        }
    }
};

int main() {
    Library lib;
    int choice, id;
    string title, author;

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n2. Issue Book\n3. Return Book\n4. Display Books\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter book ID, Title, Author: ";
                cin >> id >> ws;
                getline(cin, title);
                getline(cin, author);
                lib.addBook(id, title, author);
                break;
            case 2:
                cout << "Enter book ID to issue: ";
                cin >> id;
                lib.issueBook(id);
                break;
            case 3:
                cout << "Enter book ID to return: ";
                cin >> id;
                lib.returnBook(id);
                break;
            case 4:
                lib.displayBooks();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}
