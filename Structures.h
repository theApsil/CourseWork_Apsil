#pragma once

#include <string>

using namespace std;

/**
 * Различные вспомогательные структуры, использующиеся при формировании справочников
 */

struct Date {
    int day;
    int month;
    int year;

    int to_days() const;

    bool operator<=(const Date &other) const;

    bool operator>=(const Date &other) const;

    bool operator<(const Date &other) const;

    bool operator>(const Date &other) const;

    string to_string() const;

    bool operator==(const Date &other) const;

    bool operator!=(const Date &other) const;
};

struct DateStatusPair {
    Date date;
    bool status;

    bool operator<=(const DateStatusPair &other) const;
    bool operator>=(const DateStatusPair &other) const;
    bool operator<(const DateStatusPair &other) const;
    bool operator>(const DateStatusPair &other) const;

    bool operator==(const DateStatusPair &other) const;
    bool operator!=(const DateStatusPair &other) const;
};

struct Time {
    int hours;
    int minutes;

    int to_minutes() const;

    bool operator<(const Time &other) const;

    bool operator>(const Time &other) const;

    bool operator==(const Time &other) const;

    string to_string() const;
};

struct Master {
    string full_name;
    string salon;
    double rating;

    bool operator==(const Master &other) const;

    bool operator!=(const Master &other) const;
};

struct Record {
    string full_name;
    string service;
    Date date;
    Time start;
    Time end;
    bool status;

    bool operator==(const Record &other) const;

    bool operator!=(const Record &other) const;
};

struct FIO {
    string full_name;

    bool operator==(const FIO &other) const;

    bool operator!=(const FIO &other) const;
};

namespace std {
    template<>
    struct hash<FIO> {
        int operator()(const FIO &p) const {
            int hh = 0;
            for (char ch: p.full_name) {
                hh += ch;
            }
            return hh;
        }
    };
}

struct FullInfo {
    string full_name;
    string salon;
    double rating;
    string service;
    Date date;
    Time start;
    Time end;
    bool is_occupied;
};

enum class AddResult {
    SUCCESS, EXIST, NO_LINKED_MASTER, TIME_INTERSECT
};

enum class RemoveResult {
    SUCCESS, NOT_FOUND, LINKED_RECORDS
};