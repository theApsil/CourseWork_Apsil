#include "Records.h"
#include <string>
#include "ToString.h"

Records::Records() {
    this->date_status_tree = AVL<DateStatusPair, Record>();
}

void Records::add(const string &full_name, const string &service, Date date, Time start, Time end, bool status) {
    Record record = {full_name, service, date, start, end, status};
    this->date_status_tree.insert({date, status}, record);
}

void Records::remove(const string &full_name, const string &service, Date date, Time start, Time end, bool status) {
    Record record = {full_name, service, date, start, end, status};
    this->date_status_tree.remove({date, status}, record);
}

bool Records::has(const string &full_name, const string &service, Date date) {
    vector<Record> date_records = this->get_records_by_date(date);
    for (const Record &record: date_records) {
        if (record.full_name == full_name && record.service == service) {
            return true;
        }
    }
    return false;
}

bool Records::has_full_name(const string &full_name) {
    vector<Record> records = this->to_vector();
    for (Record &record: records) {
        if (record.full_name == full_name) {
            return true;
        }
    }
    return false;
}

vector<Record> Records::get_records_by_status(bool status) {
    vector<Record> result = {};
    for (Record record: this->to_vector()) {
        if (record.status == status) {
            result.push_back(record);
        }
    }
    return result;
}

vector<Record> Records::get_records_by_date(Date date) {
    vector<Record> result = {};
    for (Record record: this->to_vector()) {
        if (record.date == date) {
            result.push_back(record);
        }
    }
    return result;
}

void Records::load_file(const string &file_path) {
    auto records = parse_records_file(file_path);
    for (auto &record: records) {
        this->add(record.full_name,
                  record.service,
                  record.date,
                  record.start,
                  record.end,
                  record.status);
    }
}

void Records::save_to_file(const string &file_path) {
    ofstream out(file_path);
    auto records = this->to_vector();
    for (int i = 0; i < records.size(); i++) {
        auto record = records[i];
        out << record.full_name << " "
            << record.service << " "
            << record.date.to_string() << " "
            << record.start.to_string() << " "
            << record.end.to_string() << " "
            << record.status;
        if (i != (records.size() -
                  1)) {  // Условие, чтобы в конце файла не ставился \n, что может вызвать проблемы при чтении
            out << "\n";
        }
    }
    out.close();
}

vector<Record> Records::to_vector() {
    return this->date_status_tree.to_vector_second_value();
}

string Records::to_string_date_status_tree() {
    return this->date_status_tree.to_string(date_status_to_str, record_to_string);
}

void Records::clear() {
    this->date_status_tree.clear();
}

int Records::remove_records(const string &full_name, const string &service, Date date) {
    vector<Record> records = this->get_records_by_date(date);
    int count = 0;
    for (Record &record: records) {
        if (record.full_name == full_name && record.service == service) {
            this->remove(record.full_name, record.service, record.date, record.start, record.end, record.status);
            count++;
        }
    }
    return count;
}

vector<Record> Records::get_day_schedule(const string &full_name, Date date) {
    vector<Record> records = this->get_records_by_date(date);
    vector<Record> result = {};
    for (Record &record: records) {
        if (record.full_name == full_name) {
            result.push_back(record);
        }
    }
    return result;
}

bool Records::is_time_intersect_with_any(const string &full_name, Date date, Time start, Time end) {
    vector<Record> person_records = this->get_day_schedule(full_name, date);
    for (const Record& record: person_records) {
        bool intersect = end > record.start && start < record.end;
        if (intersect) {
            return true;
        }
    }
    return false;
}

vector<Record> Records::get_records_by_date_status(Date date, bool status) {
    DateStatusPair pair = {date, status};
    if (this->date_status_tree.has(pair)) {
        return this->date_status_tree.search(pair)->chain.to_vector();
    } else {
        return {};
    }
}
