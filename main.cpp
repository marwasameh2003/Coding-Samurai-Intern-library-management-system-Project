#include <iostream>
#include"books.h"
#include<vector>
#include <fstream>

using namespace std;

vector<Book>Catalog;

// here at the beginning of the program, all books
//in the file are stored in the catalog
void readDatafromFile()
{
    ifstream sourceFile("catalog.txt");
    if (sourceFile.is_open())
    {
        vector<string> fileContent;
        while (!sourceFile.eof())
        {
            string line;
            getline(sourceFile, line);
            fileContent.push_back(line);
        }
        sourceFile.close(); // Close the file after reading

       // bool isEmpty = true;
        if(!fileContent.empty())
        {
            for (int i = 0; i < fileContent.size() - 4; i += 5)
        {
            string name = fileContent[i];
            string id = fileContent[i + 1];
            string author = fileContent[i + 2];
            string genre = fileContent[i + 3];
            string status = fileContent[i + 4];
            Book b1(name, id, author, genre, status);
            Catalog.push_back(b1);
        }
            // Reopen the source file and clear its content
           // ofstream clearSourceFile("catalog.txt");
           // clearSourceFile.close();

        }

    }
    else
    {
        cout << "Error, could not open file\n";
    }
}

// here at the end of the program it takes the books in the catalog and store them in
// the file for the next time the program runs the books are still there
void putDataintoFile()
{
    //cout<< "book a7eh";
    ofstream clearSourceFile("catalog.txt");
    ofstream destinationFile("catalog.txt");

    //destinationFile<<"what is wrong";
    if (destinationFile.is_open())
    {
        for (int i = 0; i < Catalog.size(); i++)
        {
            string name = Catalog[i].title;
            string id = Catalog[i].ISBN;
            string author = Catalog[i].author;
            string genre = Catalog[i].genre;
            string status = Catalog[i].status;

            destinationFile << name << "\n";
            destinationFile << id << "\n";
            destinationFile << author << "\n";
            destinationFile << genre << "\n";
            destinationFile << status << "\n";
        }

        destinationFile.close(); // Close the file after writing
    }
    else
    {
        cout << "Couldn't open destination file." << endl;
    }
}

// here it checks the book availability
// 1: book is found and available
// 2: book is found but borrowed, not available for now
// 3: book is not found so it is not available
int checkBookAvailability(string id)
{
    bool found = false;
    bool available = false;
    for(int i = 0 ; i<Catalog.size();i++)
    {
        if(Catalog[i].ISBN == id)
        {
            found = true;
            if(Catalog[i].status == "available")
            {

                return 1;
            }
            else if(Catalog[i].status =="borrowed")
            {

                return 2;
            }
        }
        else if (Catalog[i].status == "unavailable")
        {

            return 3;
        }
    }
}
// here it takes books information and create a book object and add it to catalog
// initial status for book is available
void addBook()
{
    cout<< "Enter book's name: ";
    string name;
    cin>>name;
    cout<<"Enter book's Author: ";
    string author;
    cin>>author;
    cout<< "Enter book's ISBN: ";
    string id ;
    cin>>id;
    cout<<"Enter book's genre: ";
    string genre;
    cin>>genre;

    Book newBook(name,id,author,genre);
    Catalog.push_back(newBook);
    cout<<"Book created successfully!";
}

// here it removes the book with the provided isbn if it is available
void removeBook()
{
    cout<<"Enter the ISBN of the book you want to remove: ";
    string isbn;
    cin>>isbn;
    int found = checkBookAvailability(isbn);
    if(found == 1)
    {
        cout<<"Book removed successfully!";
        for(int i = 0 ; i<Catalog.size();i++)
        {
            if(Catalog[i].ISBN ==isbn)
            {
                Catalog[i].status = "unavailable";
            }
        }
    }
    else if(found ==2)
    {
        cout<<"Book can't be removed because it is borrowed";
    }
    else
    {
        cout<<"Sorry the books'ISBN you entered is unavailable\n";
    }

}
//function to search for a certain book and view its availablity
void searchBook()
{
    cout<<"Enter the ISBN of the book you want to search for: ";
    string isbn;
    cin>>isbn;
    if(checkBookAvailability(isbn)==1)
    {
        cout<< "Book with ISBN = "<< isbn<<" is found and available";
    }
    else if(checkBookAvailability(isbn) ==2)
    {
        cout<< "Book with ISBN = "<< isbn<<" is found but not available since borrowed";
    }
    else
    {
        cout<< "Sorry, could not find a book with ISBN = " <<isbn;

    }
}
// function to display all books available in our library management system
void displayAllbooks()
{
    cout<<"Title      Author       ISBN      Genre       Status\n";
    cout<<"---------------------------------------------------------------------\n";
    for(int i = 0 ; i<Catalog.size(); i++)
    {
        cout<< Catalog[i].title << "      "<<Catalog[i].author<< "      "<< Catalog[i].ISBN<< "      "<< Catalog[i].genre<< "      "<< Catalog[i].status;
        cout<<"\n---------------------------------------------------------------------\n";
        cout<<endl;
    }

}
// function to check if a book is available to be borrowed
void borrowBook()
{
    cout<<"Enter the ISBN of the book you want to borrow: ";
    string id;
    cin>>id;
    bool found = false;
    for(int i= 0; i<Catalog.size();i++)
    {
        if(Catalog[i].ISBN == id)
        {
            found = true;
            if(Catalog[i].status == "available")
            {
                Catalog[i].status = "borrowed";
                cout<<"Book borrowed successfully, Enjoy it\n";
                break;
            }
            else if(Catalog[i].status == "borrowed")
            {
                cout<<"Sorry, but the book you requested is already borrowed, try again later\n";
                break;
            }
            else
            {
                found = false;
            }

        }
    }
    if(!found)
    {
        cout<<"Sorry, the book you requested is unavailable in our library management system\n";
    }

}
// function to return borrowed book if it is already borrowed
void returnBorrowedBook()
{
    cout<<"Enter the ISBN of the book you want to return: ";
    string id;
    cin>>id;
    bool found = false;
    for(int i= 0; i<Catalog.size();i++)
    {
        if(Catalog[i].ISBN == id)
        {
            found = true;
            if(Catalog[i].status == "available")
            {
                cout<<"this book wasn't borrow, make sure of the name of the book you want to return\n";
            }
            else if(Catalog[i].status == "borrowed")
            {
                Catalog[i].status ="available";
                cout<<"Book returned successfully, thank you, see you soon ";
            }
            else
            {
                cout<<"Sorry, but this book is not in our catalog";
            }

        }
    }
    if(!found)
    {
        cout<<"Sorry, the book you requested is unavailable in our library management system\n";
    }

}
// library management system menu
void menu()
{
    cout<<"Welcome to our Library Management System \")";
    int choice = 1;
    while(choice!=7)
    {
            cout<<"\n---------------------------------------------------------------------\n";

    cout<<"\n1-Add book \n2-Remove book \n3-Search for book \n4-Display all books available\n5-Borrow a book\n6-Return a borrowed book\n7-Quit Program\n";
    int choice;
    cin>>choice;
    switch (choice){
    case 1:
        addBook();
        break;
    case 2:
        removeBook();
        break;
    case 3:
        searchBook();
        break;
    case 4:
        displayAllbooks();
        break;
    case 5:
        borrowBook();
        break;
    case 6:
        returnBorrowedBook();
        break;
    case 7:
        return;
    default:
        cout<<"invalid choice\n";
    }
    }
    cout<<"Thank You for using our Library Management System\n See you soon";
}

int main()
{
    readDatafromFile();
    menu();
    putDataintoFile();
}
