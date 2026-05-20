#include <iostream>
#include <array>       // std::array
#include <string>
#include <iomanip>     // setw, left
#include <typeinfo>    // typeid
#include <stdexcept>   // std::runtime_error

#include "Book.h"
#include "Magazine.h"
#include "DVD.h"
#include "Library.h"

// ===== Menu =====
void wyswietlMenu() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "   SYSTEM ZARZADZANIA BIBLIOTEKA" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. Wyswietl wszystkie elementy" << std::endl;
    std::cout << "2. Dodaj element" << std::endl;
    std::cout << "3. Wyszukaj po tytule" << std::endl;
    std::cout << "4. Wypozycz element" << std::endl;
    std::cout << "5. Zwroc element" << std::endl;
    std::cout << "6. Sortuj po tytule" << std::endl;
    std::cout << "7. Oblicz kare za spoznienie" << std::endl;
    std::cout << "8. Demo: konstruktor kopiujacy" << std::endl;
    std::cout << "9. Demo: typeid i dynamic_cast" << std::endl;
    std::cout << "0. Wyjscie" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Wybierz opcje: ";
}

// Generowanie kolejnego ID
int nastepneId() {
    static int nextId = 100;  // zmienna statyczna - pamięta wartość między wywołaniami
    return nextId++;
}

// ===== Demo: Konstruktor kopiujący =====
void demoKonstruktorKopiujacy() {
    std::cout << "\n===== DEMO: Konstruktor kopiujacy =====" << std::endl;

    // Tworzymy oryginalny obiekt
    Book oryginal(999, "Pan Tadeusz", "Adam Mickiewicz", 1834,
                  "Epopeja narodowa");

    std::cout << "\nOryginal:" << std::endl;
    std::cout << oryginal << std::endl;
    std::cout << "Adres streszczenia: " << (void*)oryginal.getSummary() << std::endl;

    // Konstruktor kopiujący - tworzy GŁĘBOKĄ KOPIĘ
    Book kopia(oryginal);

    std::cout << "\nKopia:" << std::endl;
    std::cout << kopia << std::endl;
    std::cout << "Adres streszczenia: " << (void*)kopia.getSummary() << std::endl;

    // Adresy są RÓŻNE - to dowodzi, że kopia jest głęboka
    if (oryginal.getSummary() != kopia.getSummary()) {
        std::cout << "\n>> Adresy sa ROZNE - gleboka kopia dziala poprawnie!" << std::endl;
    }
}

// ===== Demo: typeid i dynamic_cast (RTTI) =====
void demoRTTI(Library& biblioteka) {
    std::cout << "\n===== DEMO: typeid i dynamic_cast =====" << std::endl;

    // Pobieramy element przez wskaźnik do klasy bazowej
    try {
        MediaItem* item = biblioteka.findById(100);

        // typeid - sprawdza RZECZYWISTY typ obiektu w runtime
        std::cout << "\nElement o ID 100:" << std::endl;
        std::cout << "Typ (typeid): " << typeid(*item).name() << std::endl;

        // dynamic_cast - bezpieczne rzutowanie w dół hierarchii
        // Jeśli itemem jest Book, dynamic_cast zwraca wskaźnik do Book
        // Jeśli nie jest, zwraca nullptr
        Book* book = dynamic_cast<Book*>(item);
        if (book != nullptr) {
            std::cout << "dynamic_cast na Book: SUKCES" << std::endl;
            std::cout << "Streszczenie: " << book->getSummary() << std::endl;
        } else {
            std::cout << "dynamic_cast na Book: to nie jest ksiazka" << std::endl;
        }

        // Próba rzutowania na DVD - powinno zwrócić nullptr
        DVD* dvd = dynamic_cast<DVD*>(item);
        if (dvd != nullptr) {
            std::cout << "dynamic_cast na DVD: SUKCES" << std::endl;
        } else {
            std::cout << "dynamic_cast na DVD: nullptr (to nie jest DVD)" << std::endl;
        }
    } catch (const std::runtime_error& e) {
        std::cout << "Blad: " << e.what() << std::endl;
    }
}

// ===== Funkcja main =====
int main() {
    Library biblioteka("Miejska Biblioteka Publiczna");

    // Dodanie przykładowych elementów (new - alokacja dynamiczna)
    biblioteka.addItem(new Book(nastepneId(), "Lalka", "Boleslaw Prus", 1890,
                                "Powiesc o Wokulskim"));
    biblioteka.addItem(new Book(nastepneId(), "Quo Vadis", "Henryk Sienkiewicz", 1896,
                                "Chrzescijanie w Rzymie"));
    biblioteka.addItem(new Book(nastepneId(), "Solaris", "Stanislaw Lem", 1961,
                                "Kontakt z obcym umyslem"));
    biblioteka.addItem(new Magazine(nastepneId(), "National Geographic", "Redakcja NG", 2025, 284));
    biblioteka.addItem(new DVD(nastepneId(), "Zimna Wojna", "Pawel Pawlikowski", 2018, 89));

    // std::array - kontener o stałym rozmiarze
    std::array<std::string, 3> typy = {"Ksiazka", "Czasopismo", "DVD"};

    int wybor;

    do {
        wyswietlMenu();
        std::cin >> wybor;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Nieprawidlowe dane." << std::endl;
            continue;
        }
        std::cin.ignore(1000, '\n');

        try {  // obsługa wyjątków (try-catch)
            switch (wybor) {

            case 1:  // Wyświetl wszystkie - polimorfizm
                biblioteka.displayAll();
                break;

            case 2: {  // Dodaj element
                int typ;
                std::cout << "Typ (1-Ksiazka, 2-Czasopismo, 3-DVD): ";
                std::cin >> typ;
                std::cin.ignore(1000, '\n');

                std::string tytul, autor;
                int rok;
                std::cout << "Tytul: ";
                std::getline(std::cin, tytul);
                std::cout << "Autor: ";
                std::getline(std::cin, autor);
                std::cout << "Rok: ";
                std::cin >> rok;
                std::cin.ignore(1000, '\n');

                if (typ == 1) {
                    std::string streszczenie;
                    std::cout << "Streszczenie: ";
                    std::getline(std::cin, streszczenie);
                    biblioteka.addItem(new Book(nastepneId(), tytul, autor, rok, streszczenie));
                } else if (typ == 2) {
                    int numer;
                    std::cout << "Numer wydania: ";
                    std::cin >> numer;
                    biblioteka.addItem(new Magazine(nastepneId(), tytul, autor, rok, numer));
                } else if (typ == 3) {
                    int czas;
                    std::cout << "Czas trwania (min): ";
                    std::cin >> czas;
                    biblioteka.addItem(new DVD(nastepneId(), tytul, autor, rok, czas));
                } else {
                    std::cout << "Nieznany typ." << std::endl;
                }
                break;
            }

            case 3: {  // Wyszukaj - iteratory
                std::string fraza;
                std::cout << "Fraza: ";
                std::getline(std::cin, fraza);
                biblioteka.searchByTitle(fraza);
                break;
            }

            case 4: {  // Wypożycz - wyjątki
                int id;
                std::string osoba;
                std::cout << "ID: ";
                std::cin >> id;
                std::cin.ignore(1000, '\n');
                std::cout << "Imie i nazwisko: ";
                std::getline(std::cin, osoba);
                biblioteka.findById(id)->borrow(osoba);
                std::cout << "Wypozyczono!" << std::endl;
                break;
            }

            case 5: {  // Zwróć - wyjątki
                int id;
                std::cout << "ID: ";
                std::cin >> id;
                biblioteka.findById(id)->returnItem();
                std::cout << "Zwrocono!" << std::endl;
                break;
            }

            case 6:  // Sortuj - std::sort + funkcja porównująca
                biblioteka.sortByTitle();
                std::cout << "Posortowano po tytule." << std::endl;
                biblioteka.displayAll();
                break;

            case 7: {  // Oblicz karę - polimorfizm
                int id, dni;
                std::cout << "ID: ";
                std::cin >> id;
                std::cout << "Dni spoznienia: ";
                std::cin >> dni;

                MediaItem* item = biblioteka.findById(id);
                // Polimorfizm - calculateLateFee wywołuje wersję z klasy pochodnej
                double kara = item->calculateLateFee(dni);
                std::cout << "Typ: " << item->getType() << std::endl;
                std::cout << "Kara: " << kara << " zl" << std::endl;

                // std::array - zakresowa pętla for po tablicy typów
                std::cout << "\nStawki (uzycie std::array):" << std::endl;
                for (const std::string& t : typy) {
                    std::cout << "  " << t << std::endl;
                }
                break;
            }

            case 8:  // Demo konstruktora kopiującego
                demoKonstruktorKopiujacy();
                break;

            case 9:  // Demo RTTI (typeid, dynamic_cast)
                demoRTTI(biblioteka);
                break;

            case 0:
                std::cout << "Do widzenia!" << std::endl;
                break;

            default:
                std::cout << "Nieznana opcja." << std::endl;
                break;
            }

        } catch (const std::runtime_error& e) {
            std::cout << "[BLAD] " << e.what() << std::endl;
        }

    } while (wybor != 0);

    // Destruktor Library automatycznie zwalnia pamięć (RAII)
    return 0;
}
