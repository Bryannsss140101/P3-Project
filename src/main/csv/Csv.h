//
// Created by Bryan on 10/30/2024.
//

#ifndef READER_H
#define READER_H

#include <fstream>
#include <sstream>
#include <vector>

class Csv {
    std::string path;
    std::ifstream file;

public:
    explicit Csv(const std::string &file_name);

    ~Csv();

    std::vector<std::string> normalizer();

    template<class T>
    static std::vector<T> split(const std::string &line,
                                const char &delimiter);
};

template<class T>
std::vector<T> Csv::split(const std::string &line, const char &delimiter) {
    std::vector<T> tokens;
    std::stringstream ss(line);
    T token;

    while (std::getline(ss, token, delimiter)) {

    }
    //tokens.push_back(token);

    return tokens;
}

#endif //READER_H
