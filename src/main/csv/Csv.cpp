//
// Created by Bryan on 10/30/2024.
//
#include "Csv.h"


const DataFrame &Csv::get_dataframe() const {
    return dataframe;
}

Csv::Csv(const std::string &file_name)
    : path("../src/main/data/" + file_name), file(path) {
}

Csv::~Csv() {
    if (file.is_open())
        file.close();
}

bool Csv::read_csv() {
    if (!file.is_open())
        return false;

    const auto data = normalizer();

    for (int i = 0; i < data.size(); ++i) {
        const auto temp = split(data[i], ',');
        if (i == 0)
            dataframe.add_header(temp);
        else
            dataframe.add_row(temp);
    }

    file.close();
    return true;
}

std::vector<std::string> Csv::normalizer() {
    bool inner_quotes = false;
    std::string line;
    std::string line_normalized;
    std::vector<std::string> lines_normalized;

    while (std::getline(file, line)) {
        std::ranges::for_each(line, [&inner_quotes](const auto &c) {
            if (c == '"')
                inner_quotes = !inner_quotes;
        });

        line_normalized += line;

        if (!inner_quotes) {
            lines_normalized.push_back(line_normalized);
            line_normalized.clear();
        }
    }

    return lines_normalized;
}
