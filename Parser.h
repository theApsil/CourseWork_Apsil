#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "Structures.h"

using namespace std;

vector<Master> parse_masters_file(const string &file_path);

vector<Record> parse_records_file(const string &file_path);

Date parse_date(string date_str);

Time parse_time(string time_str);