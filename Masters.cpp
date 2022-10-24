#include "Masters.h"
#include <fstream>
#include "ToString.h"

Masters::Masters() {
    this->FIO_table = Hashtable<FIO, Master>();
    this->rating_tree = AVL<double, Master>();
}

void Masters::add(const string &full_name, const string& salon, double rating) {
    Master master = {full_name, salon, rating};
    this->FIO_table.insert({full_name}, master);
    this->rating_tree.insert(rating, master);
}

void Masters::remove(const string &full_name, const string& salon, double rating) {
    Master master = {full_name, salon, rating};
    this->FIO_table.erase({full_name}, master);
    this->rating_tree.remove(rating, master);
}

void Masters::remove(const string &full_name) {
    Master master = this->get_master_by_full_name(full_name);
    this->remove(master.full_name, master.salon, master.rating);
}

void Masters::load_file(const string &file_path) {
    auto masters = parse_masters_file(file_path);
    for (auto &master: masters) {
        this->add(master.full_name,
                  master.salon,
                  master.rating);
    }
}

void Masters::save_to_file(const string &file_path) {
    ofstream out(file_path);
    auto masters = this->to_vector();
    for (int i = 0; i < masters.size(); i++) {
        auto master = masters[i];
        out << master.full_name << " "
            << master.salon << " "
            << master.rating;
        if (i != (masters.size() - 1)) {  // Условие, чтобы в конце файла не ставился \n, что может вызвать проблемы при чтении
            out << "\n";
        }
    }
    out.close();
}

bool Masters::has(const string& full_name) {
    return this->FIO_table.has({full_name});
}

Master Masters::get_master_by_full_name(const string& full_name) {
    return this->FIO_table.find({full_name});
}

vector<Master> Masters::get_masters_by_salon(const string &salon) {
    vector<Master> result = {};
    auto masters = this->to_vector();
    for (Master &master: masters) {
        if (master.salon == salon) {
            result.push_back(master);
        }
    }
    return result;
}

vector<Master> Masters::to_vector() {
    vector<Master> result = {};
    auto items = this->FIO_table.to_vector();
    for (auto &item: items) {
        if (item.status == CONTAINS) {
            result.push_back(item.second);
        }
    }
    return result;
}

string Masters::to_string_hashtable() {
    return this->FIO_table.to_string(FIO_to_str, master_to_str);
}

string Masters::to_string_rating_tree() {
    return this->rating_tree.to_string(double_to_str, master_to_str);
}

void Masters::clear() {
    this->FIO_table.clear();
    this->rating_tree.clear();
}

vector<Master> Masters::get_masters_higher_rating(double rating) {
    vector<Master> result = {};
    auto nodes = this->rating_tree.get_nodes_higher(rating);
    for (auto node: nodes) {
        auto masters = node->chain.to_vector();
        for (auto &master: masters) {
            result.push_back(master);
        }
    }
    return result;
}

