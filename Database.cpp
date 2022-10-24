#include "Database.h"

Database::Database() {
    this->masters = Masters();
    this->records = Records();
}

/**
 * Добавляет мастера в справочник "Мастера" и возвращает успешность операции
 * Возвращает:
 * SUCCESS - добавление успешно
 * EXIST - ФИО уже есть в справочнике
 */
AddResult Database::add_master(const string &full_name, const string& salon, double rating) {
    if (this->masters.has(full_name)) {
        return AddResult::EXIST;
    } else {
        this->masters.add(full_name, salon, rating);
        return AddResult::SUCCESS;
    }
}

/**
 * Добавляет запись в справочник "Записи" и возвращает успешность операции
 * Возвращает:
 * SUCCESS - Успех. Добавление успешно
 * NO_LINKED_MASTER - Провал. В "Мастерах" нет такого мастера
 * TIME_INTERSECT - Провал. У мастера пересекается время
 */
AddResult Database::add_record(const string &full_name, const string &service, Date date, Time start, Time end, bool status) {
    if (this->masters.has(full_name)) {
        if (this->records.is_time_intersect_with_any(full_name, date, start, end)) {
            return AddResult::TIME_INTERSECT;
        } else {
            this->records.add(full_name, service, date, start, end, status);
            return AddResult::SUCCESS;
        }
    } else {
        return AddResult::NO_LINKED_MASTER;
    }
}

/**
 * Удаляет мастера из справочника "Мастера" и возвращает успешность операции
 * Возвращает:
 * SUCCESS - Успех. Удаление успешно
 * NOT_FOUND - Провал. Запись не найдена
 * LINKED_RECORDS - Провал. Существуют связанные с мастером записи
 */
RemoveResult Database::remove_master(const string &full_name) {
    if (this->masters.has(full_name)) {
        if (this->records.has_full_name(full_name)) {
            return RemoveResult::LINKED_RECORDS;
        } else {
            this->masters.remove(full_name);
            return RemoveResult::SUCCESS;
        }
    } else {
        return RemoveResult::NOT_FOUND;
    }
}

/**
 * Удаляет запись из справочника "Записи" и возвращает успешность операции
 * Возвращает:
 * SUCCESS - удаление успешно
 * NOT_FOUND - запись не найдена
 */
RemoveResult Database::remove_record(const string &full_name, const string &service, Date date) {
    int del_count = this->records.remove_records(full_name, service, date);
    if (del_count == 0) {  // Если не удалено ни одной такой записи (т.к. их не существует)
        return RemoveResult::NOT_FOUND;
    } else {
        return RemoveResult::SUCCESS;
    }
}

void Database::load_masters_file(const string &file_path) {
    this->masters.clear();  // Обнуляем справочник, чтобы значения не добавлялись к прошлым
    this->masters.load_file(file_path);
}

void Database::load_records_file(const string &file_path) {
    this->records.clear();  // Обнуляем справочник, чтобы значения не добавлялись к прошлым
    this->records.load_file(file_path);
}

void Database::save_masters_to_file(const string &file_path) {
    this->masters.save_to_file(file_path);
}

void Database::save_records_to_file(const string &file_path) {
    this->records.save_to_file(file_path);
}

string Database::to_string_masters_table() {
    return this->masters.to_string_hashtable();
}

string Database::to_string_masters_FIO_tree() {
    return this->masters.to_string_rating_tree();
}

string Database::to_string_records_date_status_tree() {
    return this->records.to_string_date_status_tree();
}

vector<FullInfo> Database::search(double min_rating, Date date, bool status) {
    vector<FullInfo> result = {};
    vector<Record> date_status_records = this->records.get_records_by_date_status(date, status);
    for (const Record& record: date_status_records) {
        Master master = this->masters.get_master_by_full_name(record.full_name);
        if (master.rating >= min_rating) {  // Если запись подходит
            FullInfo info = {
                    master.full_name,
                    master.salon,
                    master.rating,
                    record.service,
                    record.date,
                    record.start,
                    record.end,
                    record.status
            };
            result.push_back(info);
        }
    }
    return result;
}

/**
 * Производит поиск по параметрам и переводит его в красивую форму в строке
 */
string Database::search_to_string(double min_rating, Date date, bool status) {
    string result = "";
    auto search_result = this->search(min_rating, date, status);
    for (FullInfo &info: search_result) {
        result += "ФИО: " + info.full_name + "\n" +
                  "Услуга: " + info.service + "\n" +
                  "Дата: " + info.date.to_string() + "\n" +
                  "Время начала: " + info.start.to_string() + "\n" +
                  "Время окончания: " + info.end.to_string() + "\n" +
                  "Салон: " + info.salon + "\n\n";
    }
    return result;
}

Master Database::find_master_by_FIO(const string &full_name) {
    return this->masters.get_master_by_full_name(full_name);
}

vector<Master> Database::find_masters_by_salon(const string& salon) {
    return this->masters.get_masters_by_salon(salon);
}

vector<Record> Database::find_records_by_date(Date date) {
    return this->records.get_records_by_date(date);
}

vector<Record> Database::find_records_by_status(bool status) {
    return this->records.get_records_by_status(status);
}

vector<Master> Database::get_all_masters() {
    return this->masters.to_vector();
}

vector<Record> Database::get_all_records() {
    return this->records.to_vector();
}

bool Database::has_FIO_in_masters(const string &full_name) {
    return this->masters.has(full_name);
}

bool Database::has_FIO_in_records(const string &full_name) {
    return this->records.has_full_name(full_name);
}

vector<Master> Database::find_masters_higher_rating(double min_rating) {
    return this->masters.get_masters_higher_rating(min_rating);
}

vector<Record> Database::find_records_by_date_stauts(Date date, bool status) {
    return this->records.get_records_by_date_status(date, status);
}
