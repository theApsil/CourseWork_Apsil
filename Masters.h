#pragma once

#include "AVL.h"
#include "Hashtable.h"
#include "Parser.h"

using namespace std;

/**
 * Справочник "Мастера"
 */
class Masters {
public:
    Masters();

    void load_file(const string &file_path);

    void save_to_file(const string &file_path);

    bool has(const string& full_name);

    Master get_master_by_full_name(const string& full_name);

    vector<Master> get_masters_by_salon(const string& salon);

    vector<Master> get_masters_higher_rating(double rating);

    void add(const string &full_name, const string& salon, double rating);

    void remove(const string &full_name, const string& salon, double rating);

    void remove(const string &full_name);

    vector<Master> to_vector();

    string to_string_hashtable();

    string to_string_rating_tree();

    void clear();

private:
    Hashtable<FIO, Master> FIO_table;
    AVL<double, Master> rating_tree;
};

