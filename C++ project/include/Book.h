#pragma once

#include "MediaItem.h"

// Book dziedziczy po MediaItem (relacja "is-a": Book jest MediaItem)
class Book : public MediaItem {
private:
    char* summary;  // surowy wskaźnik - potrzebny do konstruktora kopiującego

public:
    // Konstruktor
    Book(int id, const std::string& title, const std::string& author,
         int year, const std::string& summaryText);

    // Konstruktor kopiujący - głęboka kopia
    Book(const Book& other);

    // Operator przypisania - głęboka kopia
    Book& operator=(const Book& other);

    // Destruktor - zwalnia pamięć (delete[])
    ~Book() override;

    // Nadpisanie metod czysto wirtualnych (override)
    std::string getType() const override;
    double calculateLateFee(int daysLate) const override;
    void display(std::ostream& os) const override;

    // Getter
    const char* getSummary() const;
};

