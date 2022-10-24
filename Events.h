#pragma once

#include "AVL.h"
#include "Hashtable.h"
#include "Parser.h"

using namespace std;


class Events {
public:
    void load_file(const string &file_path);

    void save_to_file(const string &file_path);

    bool has(const string &region, const string &event_name);

    bool has(const string &event_name);

    Event get_event_by_name(const string &event_name);

    vector<Event> get_events_higher_rating(int rating);

    void add(const string &region, const string &event_name, int rating);

    void remove(const string &region, const string &event_name, int rating);

    void remove(const string &region, const string &event_name);

    vector<Event> to_vector();

    string to_string_hashtable();

    string to_string_rating_tree();

    void clear();

private:
    Hashtable<string, Event> event_name_table;
    AVL<int, Event> rating_tree;
};

