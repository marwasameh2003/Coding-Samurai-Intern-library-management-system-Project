#ifndef BOOKS_H_INCLUDED
#define BOOKS_H_INCLUDED
#include<iostream>
using namespace std;
class Book
{
public:
    string title;
    string ISBN;
    string author;
    string genre;
    string status;
    Book(string t , string id , string writer, string g,string s= "available")
    {
        title = t;
        ISBN = id;
        author = writer;
        genre = g;
        status = s;
    }
    void setTitle(string t)
    {
        title = t;
    }
    void setAuthor(string a)
    {
        author = a;
    }
    void setISBN(string id)
    {
        ISBN = id;
    }
    void setGenre(string g)
    {
        genre = g;
    }
    string getTitle()
    {
        return title;
    }
    string getAuthor()
    {
        return author;
    }
    string getISBN()
    {
        return ISBN;
    }
    string getGenre()
    {
        return genre;
    }
};


#endif // BOOKS_H_INCLUDED
