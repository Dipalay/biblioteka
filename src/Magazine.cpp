#include "Magazine.h"

Magazine::Magazine(int id, const std::string& title, const std::string& author,
                   int year, int issueNumber)
    : MediaItem(id, title, author, year), issueNumber(issueNumber) {}

Magazine::~Magazine() {}

std::string Magazine::getType() const {
    return "Czasopismo";
}

double Magazine::calculateLateFee(int daysLate) const {
    return daysLate * 0.30;  // 0.30 zł za dzień
}

void Magazine::display(std::ostream& os) const {
    MediaItem::display(os);
    os << " | Nr:" << issueNumber;
}

int Magazine::getIssueNumber() const {
    return issueNumber;
}
