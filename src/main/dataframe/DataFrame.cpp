//
// Created by Bryan on 11/13/2024.
//

#include "DataFrame.h"

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

DataFrame &DataFrame::operator=(const DataFrame &other) {
    this->data = other.data;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const DataFrame &other) {
    os << other.data << std::endl;
    return os;
}
