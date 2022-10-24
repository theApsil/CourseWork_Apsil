#include "Events.h"
#include <fstream>
#include "ToString.h"


void Events::add(const string &region, const string &event_name, int rating) {
    Event event = {region, event_name, rating};
    this->event_name_table.insert(event_name, event);
    this->rating_tree.insert(rating, event);
}

void Events::remove(const string &region, const string &event_name, int rating) {
    Event event = {region, event_name, rating};
    this->event_name_table.erase(event_name);
    this->rating_tree.remove(rating, event);
}

void Events::remove(const string &region, const string &event_name) {
    Event event = this->get_event_by_name(event_name);
    this->remove(event.region, event.event_name, event.rating);
}

void Events::load_file(const string &file_path) {
    auto events = parse_events_file(file_path);
    for (auto &event: events) {
        this->add(event.region,
                  event.event_name,
                  event.rating);
    }
}

void Events::save_to_file(const string &file_path) {
    ofstream out(file_path);
    auto events = this->to_vector();
    for (int i = 0; i < events.size(); i++) {
        auto event = events[i];
        out << event.region << ";"
            << event.event_name << ";"
            << event.rating;
        if (i != (events.size() -
                  1)) {  // Условие, чтобы в конце файла не ставился \n, что может вызвать проблемы при чтении
            out << "\n";
        }
    }
    out.close();
}

bool Events::has(const string &region, const string &event_name) {
    return this->event_name_table.has(event_name) &&
           this->event_name_table.find(event_name).region == region;
}

bool Events::has(const string &event_name) {
    return this->event_name_table.has(event_name);
}

Event Events::get_event_by_name(const string &event_name) {
    return this->event_name_table.find(event_name);
}

vector<Event> Events::to_vector() {
    vector<Event> result = {};
    auto items = this->event_name_table.to_vector();
    for (auto &item: items) {
        if (item.status == CONTAINS) {
            result.push_back(item.second);
        }
    }
    return result;
}

string Events::to_string_hashtable() {
    return this->event_name_table.to_string(str_to_str, event_to_str);
}

string Events::to_string_rating_tree() {
    return this->rating_tree.to_string(int_to_str, event_to_str);
}

void Events::clear() {
    this->event_name_table.clear();
    this->rating_tree.clear();
}

vector<Event> Events::get_events_higher_rating(int rating) {
    vector<Event> result = {};
    auto nodes = this->rating_tree.get_nodes_higher(rating);
    for (auto node: nodes) {
        auto clients = node->chain.to_vector();
        for (auto &client: clients) {
            result.push_back(client);
        }
    }
    return result;
}


