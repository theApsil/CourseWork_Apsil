#include "ToString.h"

std::string FIO_to_str(FIO &key) {
    return "(" + key.full_name + ")";
}

string master_to_str(Master &master) {
    return "(" + master.full_name + ", " +
           master.salon + ", " +
           std::to_string(master.rating) + ")";
}

string record_to_string(Record &record) {
    string result = "(" + record.full_name + ", "
                    + record.service + ", "
                    + record.date.to_string() + ", "
                    + record.start.to_string() + ", "
                    + record.end.to_string() + ", "
                    + std::to_string(record.status) + ")";
    return result;
}

string date_to_str(Date &date) {
    return date.to_string();
}

string date_status_to_str(DateStatusPair &pair) {
    return "(" + date_to_str(pair.date) + ", " + std::to_string(pair.status) + ")";
}


string double_to_str(double &num) {
    return std::to_string(num);
}

string bool_to_str(bool &num) {
    return std::to_string(num);
}