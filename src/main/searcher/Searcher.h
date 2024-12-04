//
// Created by Bryannsss.
//

#ifndef SEARCHER_H
#define SEARCHER_H
#include "../csv/Csv.h"
#include "../trie/Trie.h"
#include <string>
#include "../suggestion-system/SuggestionSystem.h"

class Searcher {
public:
    DataFrame &get_dataframe() {
        return df;
    }

    std::vector<std::string> get_suggestions() {
        return suggestions;
    }

    explicit Searcher(const std::string &file);

    void find(const std::string &input);

private:
    DataFrame df;
    Trie title;
    Trie synopsis;
    std::vector<std::string> suggestions;

    void load(Trie &trie, const std::string &key);
};

#endif //SEARCHER_H
