//
// Created by Bryannsss.
//

#ifndef SEARCHER_H
#define SEARCHER_H
#include "../csv/Csv.h"
#include "../trie/Trie.h"
#include <string>
#include <unordered_set>

class Searcher {
public:
    explicit Searcher(const std::string &file);

    void find(const std::string &input);

private:
    DataFrame df;
    Trie title;
    Trie synopsis;

    void load(Trie &trie, const std::string &key);
};

#endif //SEARCHER_H
