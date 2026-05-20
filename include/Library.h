#pragma once

#include "MediaItem.h"
#include <vector>
#include <string>

class Library {
private:
    std::string name;
    std::vector<MediaItem*> items;  // wektor wskaźników - polimorfizm

public:
    Library(const std::string& name);
    ~Library();  // destruktor zwalnia pamięć (delete)

    // Zarządzanie kolekcją
    void addItem(MediaItem* item);
    MediaItem* findById(int id) const;

    // Wyświetlanie
    void displayAll() const;

    // Wyszukiwanie po tytule - używa iteratorów
    void searchByTitle(const std::string& phrase) const;

    // Sortowanie - algorytm std::sort
    void sortByTitle();

    // Gettery
    int getCount() const;
    std::string getName() const;
};

// Funkcja porównująca do std::sort (zamiast lambdy)
bool porownajPoTytule(MediaItem* a, MediaItem* b);

