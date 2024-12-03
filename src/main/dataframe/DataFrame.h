//
// Created by Bryan on 11/13/2024.
//

#ifndef DATAFRAME_H
#define DATAFRAME_H
#include <string>
#include <ostream>
#include <vector>

#include "../dictionary/Dictionary.h"

class DataFrame {
public:
    DataFrame() = default;

    ~DataFrame() = default;

    void add_header(const std::vector<std::string> &header);

    void add_column(const std::string &column_name);

    void add_row(const std::vector<std::string> &row);

    std::vector<std::string> get_data(const std::string &key);

    DataFrame& operator=(const DataFrame& other);

    friend std::ostream &operator<<(std::ostream &os, const DataFrame &other);

private:
    Dictionary<std::string, std::vector<std::string> > data;
};

#endif //DATAFRAME_H
