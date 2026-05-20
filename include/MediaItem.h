#pragma once

#include <string>
#include <iostream>

// Klasa abstrakcyjna - nie mozna stworzyc obiektu MediaItem
// (bo ma metody czysto wirtualne = 0)
class MediaItem {
protected:  // dostepne w klasach pochodnych
    int id;
    std::string title;
    std::string author;
    int year;
    bool borrowed;
    std::string borrower;

public:
    // Konstruktor z listą inicjalizacyjną
    MediaItem(int id, const std::string& title, const std::string& author, int year);

    // Wirtualny destruktor - wymagany przy polimorfizmie
    virtual ~MediaItem();

    // Metody czysto wirtualne (= 0) - klasy pochodne MUSZĄ je zaimplementować
    virtual std::string getType() const = 0;
    virtual double calculateLateFee(int daysLate) const = 0;

    // Metoda wirtualna - klasy pochodne MOGĄ ją nadpisać
    virtual void display(std::ostream& os) const;

    // Gettery - metody stałe (const), nie zmieniają obiektu
    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    int getYear() const;
    bool isBorrowed() const;

    // Wypożyczanie i zwrot - rzucają wyjątki
    void borrow(const std::string& borrowerName);
    void returnItem();

    // Przeciążanie operatorów
    bool operator==(const MediaItem& other) const;
    bool operator<(const MediaItem& other) const;

    // Deklaracja przyjaciela - operator<< ma dostęp do prywatnych pól
    friend std::ostream& operator<<(std::ostream& os, const MediaItem& item);
};

