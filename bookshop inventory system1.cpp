#include <iostream>
#include <vector>
#include <string>

class Book {
public:
    int id;
    std::string title;
    int count;

    // Constructor
    Book(int bookId, const std::string& bookTitle, int bookCount) : id(bookId), title(bookTitle), count(bookCount) {}

    // Function to display book information
    void display() const {
        std::cout << "Book ID: " << id << ", Title: " << title << ", Count: " << count << std::endl;
    }
};

class BookInventory {
private:
    std::vector<Book*> books;

public:
    // Function to add a book
    void addBook(int bookId, const std::string& bookTitle, int bookCount) {
        Book* newBook = new Book(bookId, bookTitle, bookCount);
        books.push_back(newBook);
        std::cout << "Book added successfully." << std::endl;
    }

    // Function to display all books
    void displayAllBooks() const {
        std::cout << "Inventory:" << std::endl;
        for (const auto& book : books) {
            book->display();
        }
    }

    // Function to search for a book by ID
    std::vector<Book*> searchById(int bookId) const {
        std::vector<Book*> results;
        for (const auto& book : books) {
            if (book->id == bookId) {
                results.push_back(book);
            }
        }
        return results;
    }

    // Function to search for books based on a single parameter (e.g., title)
    std::vector<Book*> searchByParameter(const std::string& parameter) const {
        std::vector<Book*> results;
        for (const auto& book : books) {
            // Modify the condition based on the parameter you want to search for (e.g., title)
            if (book->title.find(parameter) != std::string::npos) {
                results.push_back(book);
            }
        }
        return results;
    }

    // Function to update book count when a customer purchases a book
    void purchaseBook(int bookId, int quantity) {
        for (auto& book : books) {
            if (book->id == bookId) {
                book->count -= quantity;
                std::cout << "Purchase successful. Updated book count." << std::endl;
                return;
            }
        }
        std::cout << "Book not found." << std::endl;
    }

    // Destructor to free allocated memory
    ~BookInventory() {
        for (auto& book : books) {
            delete book;
        }
        books.clear();
    }
};

int main() {
    BookInventory inventory;

    // Adding books to inventory
    inventory.addBook(1, "The Great Gatsby", 10);
    inventory.addBook(2, "To Kill a Mockingbird", 15);
    inventory.addBook(3, "1984", 8);

    // Displaying all books in inventory
    inventory.displayAllBooks();

    // Searching for a book by ID
    int searchId = 2;
    std::cout << "Searching for book with ID " << searchId << ":" << std::endl;
    std::vector<Book*> searchResultsById = inventory.searchById(searchId);
    for (const auto& result : searchResultsById) {
        result->display();
    }

    // Searching for books based on a single parameter (e.g., title)
    std::string searchTitle = "1984";
    std::cout << "Searching for books with title '" << searchTitle << "':" << std::endl;
    std::vector<Book*> searchResultsByParameter = inventory.searchByParameter(searchTitle);
    for (const auto& result : searchResultsByParameter) {
        result->display();
    }

    // Updating book count when a customer purchases a book
    int purchaseBookId = 1;
    int purchaseQuantity = 2;
    inventory.purchaseBook(purchaseBookId, purchaseQuantity);

    // Displaying updated inventory
    inventory.displayAllBooks();

    return 0;
}
