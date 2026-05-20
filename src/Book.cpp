#include "Book.h"
#include <cstring>

// Konstruktor - alokuje pamięć dynamicznie (new)
Book::Book(int id, const std::string& title, const std::string& author,
           int year, const std::string& summaryText)
    : MediaItem(id, title, author, year)
{
    summary = new char[summaryText.length() + 1];
    std::strcpy(summary, summaryText.c_str());
}

// Konstruktor kopiujący - głęboka kopia
// Tworzymy nowy obszar pamięci i kopiujemy dane
// Bez tego byłaby płytka kopia (oba obiekty wskazywałyby na ten sam adres)
Book::Book(const Book& other)
    : MediaItem(other.id, other.title, other.author, other.year)
{
    summary = new char[std::strlen(other.summary) + 1];
    std::strcpy(summary, other.summary);
    borrowed = other.borrowed;
    borrower = other.borrower;
}

// Operator przypisania - głęboka kopia
Book& Book::operator=(const Book& other) {
    if (this != &other) {  // ochrona przed samoprzypusaniem (a = a)
        delete[] summary;  // zwolnij starą pamięć

        id = other.id;
        title = other.title;
        author = other.author;
        year = other.year;
        borrowed = other.borrowed;
        borrower = other.borrower;

        summary = new char[std::strlen(other.summary) + 1];
        std::strcpy(summary, other.summary);
    }
    return *this;
}

// Destruktor - zwalnia pamięć (RAII)
Book::~Book() {
    delete[] summary;
}

// Nadpisanie metod czysto wirtualnych
std::string Book::getType() const {
    return "Ksiazka";
}

double Book::calculateLateFee(int daysLate) const {
    return daysLate * 0.50;  // 0.50 zł za dzień
}

void Book::display(std::ostream& os) const {
    MediaItem::display(os);  // wywołanie metody klasy bazowej
    os << " | " << summary;
}

const char* Book::getSummary() const {
    return summary;
}
