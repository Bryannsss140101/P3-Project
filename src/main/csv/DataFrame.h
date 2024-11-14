//
// Created by Bryan on 11/13/2024.
//

#ifndef DATAFRAME_H
#define DATAFRAME_H
#include <ostream>
#include <string>
#include <vector>

typedef std::string key;
typedef std::vector<std::string> value;
// typedef std::vector<std::pair<key, value> > > dictionary;

class DataFrame {
public:
    //    dictionary get_data() const;

    DataFrame() = default;

    ~DataFrame() = default;

    void add_column(const std::string &column_name);

    void add_row(const std::vector<std::string> &row);

    //std::vector<std::string>

    //  friend std::ostream &operator<<(std::ostream &os, const DataFrame &other);



private:
    //dictionary data;
};

#endif //DATAFRAME_H
