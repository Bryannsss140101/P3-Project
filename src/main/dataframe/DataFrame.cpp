//
// Created by Bryan on 11/13/2024.
//

#include "DataFrame.h"
#include <algorithm>

int DataFrame::search(const std::string &colum_name, const std::string &word) {
    auto aux = data[colum_name];
    const auto it = std::ranges::find_if(aux, [&](const auto &e) {
        return e == word;
    });

    if (it != aux.end())
        return std::distance(aux.begin(), it);
    return -1;
}

void DataFrame::add_header(const std::vector<std::string> &header) {
    std::ranges::for_each(header, [this](const auto &e) {
        add_column(e);
    });
}

void DataFrame::add_column(const std::string &column_name) {
    data.add(column_name, std::vector<std::string>());
}

void DataFrame::add_row(const std::vector<std::string> &row) {
    for (int i = 0; i < data.count(); ++i) {
        auto value = i < row.size() ? row[i] : "";
        auto key = data.get_key(i);

        data[key].push_back(value);
    }
}

std::vector<std::string> DataFrame::get_data(const std::string &key) {
    return data[key];
}

std::string DataFrame::get_data(const std::string &key, const int index) {
    return data[key][index];
}

DataFrame &DataFrame::operator=(const DataFrame &other) {
    this->data = other.data;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const DataFrame &other) {
    os << other.data << std::endl;
    return os;
}
