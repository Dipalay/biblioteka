#pragma once

#include "MediaItem.h"

class Magazine : public MediaItem {
private:
    int issueNumber;

public:
    Magazine(int id, const std::string& title, const std::string& author,
             int year, int issueNumber);
    ~Magazine() override;

    std::string getType() const override;
    double calculateLateFee(int daysLate) const override;
    void display(std::ostream& os) const override;

    int getIssueNumber() const;
};

