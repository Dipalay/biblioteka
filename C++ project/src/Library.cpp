#include "Library.h"
#include <algorithm>  // std::sort
#include <iostream>
#include <stdexcept>

// Konstruktor
Library::Library(const std::string& name) : name(name) {}

// Destruktor - RAII: zwalniamy pamięć wszystkich elementów
Library::~Library() {
    for (int i = 0; i < (int)items.size(); i++) {
        delete items[i];
    }
}

// Dodawanie elementu
void Library::addItem(MediaItem* item) {
    items.push_back(item);
}

// Szukanie po ID - jawne użycie iteratorów (begin/end)
MediaItem* Library::findById(int id) const {
    std::vector<MediaItem*>::const_iterator it;
    for (it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getId() == id) {
            return *it;
        }
    }
    throw std::runtime_error("Nie znaleziono elementu o ID: " + std::to_string(id));
}

// Wyświetlanie - zakresowa pętla for
void Library::displayAll() const {
    std::cout << "\n===== " << name << " =====" << std::endl;
    std::cout << "Liczba elementow: " << items.size() << "\n" << std::endl;

    for (const auto& item : items) {  // zakresowa pętla for
        std::cout << *item << std::endl;  // operator<< (friend + polimorfizm)
    }
}

// Wyszukiwanie po tytule - jawne użycie iteratorów
void Library::searchByTitle(const std::string& phrase) const {
    bool found = false;
    std::vector<MediaItem*>::const_iterator it;

    for (it = items.begin(); it != items.end(); ++it) {
        std::string itemTitle = (*it)->getTitle();
        // Proste sprawdzenie czy tytuł zawiera frazę
        if (itemTitle.find(phrase) != std::string::npos) {
            std::cout << **it << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "Nie znaleziono elementow." << std::endl;
    }
}

// Sortowanie - algorytm std::sort z funkcją porównującą
void Library::sortByTitle() {
    std::sort(items.begin(), items.end(), porownajPoTytule);
}

// Gettery
int Library::getCount() const {
    return (int)items.size();
}

std::string Library::getName() const {
    return name;
}

// Funkcja porównująca - używa operator< z MediaItem
bool porownajPoTytule(MediaItem* a, MediaItem* b) {
    return *a < *b;  // wywołuje MediaItem::operator<
}
