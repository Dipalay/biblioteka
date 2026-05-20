#pragma once

#include "MediaItem.h"

class DVD : public MediaItem {
private:
    int duration;  // czas trwania w minutach

public:
    DVD(int id, const std::string& title, const std::string& author,
        int year, int duration);
    ~DVD() override;

    std::string getType() const override;
    double calculateLateFee(int daysLate) const override;
    void display(std::ostream& os) const override;

    int getDuration() const;
};

