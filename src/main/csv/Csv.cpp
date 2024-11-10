//
// Created by Bryan on 10/30/2024.
//
#include "Csv.h"

#include <algorithm>

Csv::Csv(const std::string &file_name)
    : path("../src/main/data/" + file_name), file(path) {
    if (!file.is_open())
        throw std::runtime_error("File could not be opened.");
}

Csv::~Csv() {
    if (file.is_open())
        file.close();
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
