
#include <iostream>
#include <vector>
#include <string>

class Book {
protected:
    std::string title;
    std::string author;
    double price;

public:
    Book(const std::string& title, const std::string& author, double price)
        : title(title), author(author), price(price) {}

    virtual void display() const {
        std::cout << "Title: " << title << ", Author: " << author << ", Price: $" << price << std::endl;
    }
};

class FictionBook : public Book {
public:
    FictionBook(const std::string& title, const std::string& author, double price)
        : Book(title, author, price) {}

    void display() const override {
        std::cout << "Fiction Book - ";
        Book::display();
    }
};

class NonFictionBook : public Book {
public:
    NonFictionBook(const std::string& title, const std::string& author, double price)
        : Book(title, author, price) {}

    void display() const override {
        std::cout << "Non-Fiction Book - ";
        Book::display();
    }
};

class Bookstore {
private:
    std::vector<Book*> books;

public:
    void addBook(Book* book) {
        books.push_back(book);
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book->display();
        }
    }

    ~Bookstore() {
        for (auto& book : books) {
            delete book;
        }
    }
};

int main() {
    Bookstore bookstore;
    bookstore.addBook(new FictionBook("The Great Gatsby", "F. Scott Fitzgerald", 12.99));
    bookstore.addBook(new NonFictionBook("Sapiens: A Brief History of Humankind", "Yuval Noah Harari", 18.50));

    bookstore.displayAllBooks();

    return 0;
}