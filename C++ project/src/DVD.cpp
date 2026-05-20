#include "DVD.h"

DVD::DVD(int id, const std::string& title, const std::string& author,
         int year, int duration)
    : MediaItem(id, title, author, year), duration(duration) {}

DVD::~DVD() {}

std::string DVD::getType() const {
    return "DVD";
}

double DVD::calculateLateFee(int daysLate) const {
    return daysLate * 1.00;  // 1.00 zł za dzień
}

void DVD::display(std::ostream& os) const {
    MediaItem::display(os);
    os << " | " << duration << " min";
}

int DVD::getDuration() const {
    return duration;
}
