//
// Created by Bryan on 11/13/2024.
//

#include "DataFrame.h"
#include <algorithm>

/*
dictionary DataFrame::get_data() const {
    return data;
}

void DataFrame::add_column(const std::string &column_name) {
    const auto it = std::ranges::find_if(data, [&](const auto &e) {
        return column_name == e.first;
    });

    if (it == data.end())
        data.push_back({column_name, std::vector<std::string>()});
}

void DataFrame::add_row(const std::vector<std::string> &row) {
    int i = 0;
    std::ranges::
            for_each(data, [&](auto &e) {
                auto value = i < row.size() ? row[i] : "";
                e.second.push_back(value);
                i++;
            });
}

std::ostream &operator <<(std::ostream &os, const std::vector<std::string> &other) {
    std::ranges::for_each(other, [&](const auto &item) {
        os << item << " ";
    });

    return os;
}

std::ostream &operator<<(std::ostream &os, const DataFrame &other) {
    std::ranges::for_each(other.data, [&](const auto &e) {
        os
                << "[" << e.first << "]: "
                << "{ " << e.second << "}"
                << std::endl;
    });
    return os;
}
*/