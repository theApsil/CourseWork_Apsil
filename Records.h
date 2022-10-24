#pragma once

#include <string>
#include "AVL.h"
#include "Hashtable.h"
#include "Parser.h"

using namespace std;

/**
 * Справочник "Записи"
 */
class Records {
public:
    Records();

    void load_file(const string &file_path);

    void save_to_file(const string &file_path);

    bool has(const string& full_name, const string& service, Date date);

    bool has_full_name(const string &full_name);

    vector<Record> get_records_by_date(Date date);

    vector<Record> get_records_by_status(bool status);

    vector<Record> get_records_by_date_status(Date date, bool status);

    void add(const string& full_name, const string& service, Date date, Time start, Time end, bool status);

    void remove(const string& full_name, const string& service, Date date, Time start, Time end, bool status);

    int remove_records(const string& full_name, const string& service, Date date);

    vector<Record> to_vector();

    string to_string_date_status_tree();

    void clear();

    vector<Record> get_day_schedule(const string& full_name, Date date);

    bool is_time_intersect_with_any(const string& full_name, Date date, Time start, Time end);

private:
    AVL<DateStatusPair, Record> date_status_tree;
};
