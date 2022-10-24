#pragma once

#include "Masters.h"
#include "Records.h"
#include <string>

/**
 * Класс, объединяющий справочник "Мастера" и "Записи" для удобного использования.
 * Также позволяет проверять связь записей при удалении
 */
class Database {
public:
    Database();

    void load_masters_file(const string &file_path);

    void load_records_file(const string &file_path);

    void save_masters_to_file(const string &file_path);

    void save_records_to_file(const string &file_path);

    AddResult add_master(const string &full_name, const string& salon, double rating);

    AddResult add_record(const string &full_name, const string &service, Date date, Time start, Time end, bool status);

    RemoveResult remove_master(const string &full_name);

    RemoveResult remove_record(const string &full_name, const string &service, Date date);

    bool has_FIO_in_masters(const string &full_name);

    bool has_FIO_in_records(const string &full_name);

    vector<Master> get_all_masters();

    vector<Record> get_all_records();

    string to_string_masters_table();

    string to_string_masters_FIO_tree();

    string to_string_records_date_status_tree();

    // Задачи поиска:

    vector<FullInfo> search(double min_rating, Date date, bool status);

    string search_to_string(double min_rating, Date date, bool status);

    Master find_master_by_FIO(const string &full_name);

    vector<Master> find_masters_by_salon(const string &salon);

    vector<Master> find_masters_higher_rating(double min_rating);

    vector<Record> find_records_by_date(Date date);

    vector<Record> find_records_by_status(bool status);

    vector<Record> find_records_by_date_stauts(Date date, bool status);

private:
    Masters masters;
    Records records;
};
