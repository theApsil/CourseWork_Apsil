#include "Structures.h"
#include <stdexcept>

int Date::to_days() const {
    return day + month * 30 + year * 365;
}

bool Date::operator<=(const Date &other) const {
    return this->to_days() <= other.to_days();
}

bool Date::operator>=(const Date &other) const {
    return this->to_days() >= other.to_days();
}

string Date::to_string() const {
    string d = std::to_string(day);
    if (day < 10) {
        d = "0" + d;
    }
    string m = std::to_string(month);
    if (month < 10) {
        m = "0" + m;
    }
    string y = std::to_string(year);

    if (day != -1) {  // Если дата существует
        return d + "." + m + "." + y;
    } else {
        return "";
    }
}

bool Date::operator==(const Date &other) const {
    return (day == other.day && month == other.month && year == other.year);
}

bool Date::operator!=(const Date &other) const {
    return !(*this == other);
}

bool Date::operator<(const Date &other) const {
    return this->to_days() < other.to_days();
}

bool Date::operator>(const Date &other) const {
    return this->to_days() > other.to_days();
}


bool Master::operator==(const Master &other) const {
    return (full_name == other.full_name &&
            salon == other.salon &&
            rating == other.rating);
}

bool Master::operator!=(const Master &other) const {
    return !(*this == other);
}

bool Record::operator==(const Record &other) const {
    return (full_name == other.full_name &&
            service == other.service &&
            date == other.date &&
            start == other.start &&
            end == other.end &&
            status == other.status);
}

bool Record::operator!=(const Record &other) const {
    return !(*this == other);
}

int Time::to_minutes() const {
    return this->hours * 60 + this->minutes;
}

bool Time::operator<(const Time &other) const {
    return this->to_minutes() < other.to_minutes();
}

bool Time::operator>(const Time &other) const {
    return this->to_minutes() > other.to_minutes();
}

bool Time::operator==(const Time &other) const {
    return hours == other.hours && minutes == other.minutes;
}

string Time::to_string() const {
    string h = std::to_string(hours);
    if (hours < 10) {
        h = "0" + h;
    }
    string m = std::to_string(minutes);
    if (minutes < 10) {
        m = "0" + m;
    }
    return h + ":" + m;
}

bool FIO::operator==(const FIO &other) const {
    return full_name == other.full_name;
}

bool FIO::operator!=(const FIO &other) const {
    return full_name != other.full_name;
}

bool DateStatusPair::operator<=(const DateStatusPair &other) const {
    return date < other.date ||
           date == other.date && status <= other.status;
}

bool DateStatusPair::operator>=(const DateStatusPair &other) const {
    return date > other.date ||
           date == other.date && status >= other.status;
}

bool DateStatusPair::operator<(const DateStatusPair &other) const {
    return date < other.date ||
           date == other.date && status < other.status;
}

bool DateStatusPair::operator>(const DateStatusPair &other) const {
    return date > other.date ||
           date == other.date && status > other.status;
}

bool DateStatusPair::operator==(const DateStatusPair &other) const {
    return date == other.date && status == other.status;
}

bool DateStatusPair::operator!=(const DateStatusPair &other) const {
    return !(*this == other);
}
