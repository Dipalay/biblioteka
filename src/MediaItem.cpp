#include "MediaItem.h"
#include <stdexcept>
#include <iomanip>

MediaItem::MediaItem(int id, const std::string& title, const std::string& author, int year)
    : id(id), title(title), author(author), year(year), borrowed(false), borrower("") {}

MediaItem::~MediaItem() {}

void MediaItem::display(std::ostream& os) const {
    os << std::left
       << std::setw(12) << getType()
       << "ID:" << std::setw(5) << id
       << std::setw(22) << title
       << std::setw(22) << author
       << "Rok:" << std::setw(6) << year;

    if (borrowed) {
        os << " [Wypozyczony: " << borrower << "]";
    } else {
        os << " [Dostepny]";
    }
}

int MediaItem::getId() const { return id; }
std::string MediaItem::getTitle() const { return title; }
std::string MediaItem::getAuthor() const { return author; }
int MediaItem::getYear() const { return year; }
bool MediaItem::isBorrowed() const { return borrowed; }

void MediaItem::borrow(const std::string& borrowerName) {
    if (borrowed) {
        throw std::runtime_error("Element jest juz wypozyczony: " + title);
    }
    borrowed = true;
    borrower = borrowerName;
}

void MediaItem::returnItem() {
    if (!borrowed) {
        throw std::runtime_error("Element nie jest wypozyczony: " + title);
    }
    borrowed = false;
    borrower = "";
}

bool MediaItem::operator==(const MediaItem& other) const {
    return id == other.id;
}

bool MediaItem::operator<(const MediaItem& other) const {
    return title < other.title;
}

// friend - ma dostep do pol prywatnych
std::ostream& operator<<(std::ostream& os, const MediaItem& item) {
    item.display(os);
    return os;
}
