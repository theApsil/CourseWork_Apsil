#include "Parser.h"

using namespace std;

vector<Master> parse_masters_file(const string &file_path) {
    ifstream file(file_path);

    vector<Master> result;
    string first_name;
    string second_name;
    string third_name;
    string full_name;
    string salon;
    double rating;

    while (!file.eof()) {
        file >> first_name
             >> second_name
             >> third_name
             >> salon
             >> rating;
        full_name = first_name + " " + second_name + " " + third_name;
        Master master = {
                full_name,
                salon,
                rating
        };
        result.push_back(master);
    }
    file.close();
    return result;
}

vector<Record> parse_records_file(const string &file_path) {
    ifstream file(file_path);

    vector<Record> result = {};
    string first_name;
    string second_name;
    string third_name;
    string full_name;
    string service;
    string date;
    string start;
    string end;
    bool status;

    while (!file.eof()) {
        file >> first_name
             >> second_name
             >> third_name
             >> service
             >> date
             >> start
             >> end
             >> status;
        full_name = first_name + " " + second_name + " " + third_name;
        Record record = {
                full_name,
                service,
                parse_date(date),
                parse_time(start),
                parse_time(end),
                status
        };
        result.push_back(record);
    }
    file.close();
    return result;
}

Date parse_date(string date_str) {
    // dd.mm.yyyy
    int day = std::stoi(date_str.substr(0, 2));
    int month = std::stoi(date_str.substr(3, 2));
    int year = std::stoi(date_str.substr(6, 4));
    return {day, month, year};
}

Time parse_time(string time_str) {
    // hh:mm
    int hours = std::stoi(time_str.substr(0, 2));
    int minutes = std::stoi(time_str.substr(3, 2));
    return {hours, minutes};
}