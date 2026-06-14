#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;

    void addBook() {
        cout << "\nEnter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        isIssued = false;
    }

    void display() {
        cout << "\n----------------------";
        cout << "\nBook ID   : " << id;
        cout << "\nTitle     : " << title;
        cout << "\nAuthor    : " << author;
        cout << "\nStatus    : " << (isIssued ? "Issued" : "Available");
        cout << "\n----------------------";
    }
};

void saveBook(Book b) {
    ofstream file("books.txt", ios::app);
    file << b.id << "|" << b.title << "|" << b.author << "|" << b.isIssued << endl;
    file.close();
}

void addBook() {
    Book b;
    b.addBook();
    saveBook(b);
    cout << "\nBook Added Successfully!\n";
}

void displayBooks() {
    ifstream file("books.txt");
    string line;

    cout << "\n===== BOOK LIST =====\n";

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void searchBook() {
    string keyword;
    cout << "\nEnter Title or Author to Search: ";
    cin.ignore();
    getline(cin, keyword);

    ifstream file("books.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.find(keyword) != string::npos) {
            cout << "\nFound: " << line;
            found = true;
        }
    }

    if (!found)
        cout << "\nNo matching book found!\n";

    file.close();
}

void issueOrReturn(bool issue) {
    int bookId;
    cout << "\nEnter Book ID: ";
    cin >> bookId;

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {
        int pos1 = line.find('|');
        int pos2 = line.rfind('|');

        int id = stoi(line.substr(0, pos1));
        string title = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string rest = line.substr(pos2 + 1);

        bool status = stoi(rest);

        if (id == bookId) {
            found = true;

            if (issue && status == 0) {
                status = 1;
                cout << "\nBook Issued Successfully!";
            }
            else if (!issue && status == 1) {
                status = 0;
                cout << "\nBook Returned Successfully!";
            }
            else {
                cout << "\nInvalid Operation!";
            }

            temp << id << "|" << title << "|" << status << endl;
        }
        else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found)
        cout << "\nBook Not Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n==============================";
        cout << "\n  LIBRARY MANAGEMENT SYSTEM";
        cout << "\n==============================";
        cout << "\n1. Add Book";
        cout << "\n2. Display Books";
        cout << "\n3. Search Book";
        cout << "\n4. Issue Book";
        cout << "\n5. Return Book";
        cout << "\n6. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addBook();
            break;

        case 2:
            displayBooks();
            break;

        case 3:
            searchBook();
            break;

        case 4:
            issueOrReturn(true);
            break;

        case 5:
            issueOrReturn(false);
            break;

        case 6:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}
