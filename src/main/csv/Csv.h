//
// Created by Bryan on 10/30/2024.
//

#ifndef READER_H
#define READER_H

#include <fstream>
#include <vector>
#include <sstream>
#include "../dataframe/DataFrame.h"

class Csv {
public:
    const DataFrame &get_dataframe() const;

    explicit Csv(const std::string &file_name);

    ~Csv();

    bool read_csv();

private:
    std::string path;
    std::ifstream file;
    DataFrame dataframe;

    std::vector<std::string> normalizer();
};

inline std::vector<std::string> split(const std::string &str, const char &delimiter) {
    std::vector<std::string> tokens;
    std::istringstream stream(str);
    std::string token;

    while (std::getline(stream, token, delimiter))
        tokens.push_back(token);

    return tokens;
}

#endif //READER_H
