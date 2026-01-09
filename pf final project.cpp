#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Book {
    int id;
    char title[50];
    char author[50];
    int quantity;
};

void addBook();
void displayBooks();
void searchBook();
void issueBook();
void returnBook();

int main() {
    int choice;

    do {
        system("cls");
        cout << "=====================================\n";
        cout << "        LIBRARY MANAGEMENT SYSTEM     \n";
        cout << "=====================================\n";
        cout << "1. Add New Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "-------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addBook(); break;
        case 2: displayBooks(); break;
        case 3: searchBook(); break;
        case 4: issueBook(); break;
        case 5: returnBook(); break;
        case 6: cout << "\nThank you for using Library System!\n"; break;
        default: cout << "\nInvalid Choice!\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();

    } while (choice != 6);

    return 0;
}

// ================= FUNCTIONS =================

void addBook() {
    Book b;
    ofstream file("library.txt", ios::app);

    cout << "\nEnter Book ID: ";
    cin >> b.id;
    cin.ignore();
    cout << "Enter Book Title: ";
    cin.getline(b.title, 50);
    cout << "Enter Author Name: ";
    cin.getline(b.author, 50);
    cout << "Enter Quantity: ";
    cin >> b.quantity;

    file.write((char*)&b, sizeof(b));
    file.close();

    cout << "\nBook Added Successfully!";
}

void displayBooks() {
    Book b;
    ifstream file("library.txt");

    cout << "\nID   Title                 Author               Qty\n";
    cout << "-----------------------------------------------------\n";

    while (file.read((char*)&b, sizeof(b))) {
        cout << setw(4) << b.id << " "
             << setw(20) << b.title << " "
             << setw(20) << b.author << " "
             << setw(3) << b.quantity << endl;
    }

    file.close();
}

void searchBook() {
    Book b;
    int id;
    bool found = false;
    ifstream file("library.txt");

    cout << "\nEnter Book ID to search: ";
    cin >> id;

    while (file.read((char*)&b, sizeof(b))) {
        if (b.id == id) {
            cout << "\nBook Found!";
            cout << "\nTitle: " << b.title;
            cout << "\nAuthor: " << b.author;
            cout << "\nQuantity: " << b.quantity;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nBook not found!";

    file.close();
}

void issueBook() {
    Book b;
    int id;
    bool found = false;
    fstream file("library.txt", ios::in | ios::out);

    cout << "\nEnter Book ID to issue: ";
    cin >> id;

    while (file.read((char*)&b, sizeof(b))) {
        if (b.id == id && b.quantity > 0) {
            b.quantity--;
            file.seekp(-sizeof(b), ios::cur);
            file.write((char*)&b, sizeof(b));
            cout << "\nBook Issued Successfully!";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nBook not available!";

    file.close();
}

void returnBook() {
    Book b;
    int id, days;
    bool found = false;
    fstream file("library.txt", ios::in | ios::out);

    cout << "\nEnter Book ID to return: ";
    cin >> id;
    cout << "Enter late days: ";
    cin >> days;

    while (file.read((char*)&b, sizeof(b))) {
        if (b.id == id) {
            b.quantity++;
            file.seekp(-sizeof(b), ios::cur);
            file.write((char*)&b, sizeof(b));

            if (days > 0)
                cout << "\nFine: Rs. " << days * 10;

            cout << "\nBook Returned Successfully!";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nInvalid Book ID!";

    file.close();
}

