//
// Created by Bryan on 10/30/2024.
//

#ifndef READER_H
#define READER_H

#include <fstream>
#include <vector>
#include <map>

class Csv {
public:
    std::vector<std::string> get_data() const;

    explicit Csv(const std::string &file_name);

    ~Csv();

    bool read_csv();

private:
    std::string path;
    std::ifstream file;
    std::vector<std::string> data;

    std::vector<std::string> normalizer();
};

#endif //READER_H
