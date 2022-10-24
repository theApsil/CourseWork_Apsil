#pragma once

#include <string>
#include "Structures.h"

/**
 * Функции для перевода разных структур в строку
 * Используются при переводе деревьев и хеш-таблиц в строку
 */

std::string FIO_to_str(FIO &key);

string master_to_str(Master &master);

string record_to_string(Record &record);

string date_to_str(Date &date);

string date_status_to_str(DateStatusPair &pair);

string double_to_str(double &num);

string bool_to_str(bool &num);
