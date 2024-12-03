//
// Created by Bryannsss.
//

#include "Searcher.h"
#include <algorithm>

Searcher::Searcher(const std::string &file) {
    auto csv = Csv(file);
    csv.read_csv();
    df = csv.get_dataframe();
    load(title, "title");
    //load(synopsis, "plot_synopsis");
}

void Searcher::find(const std::string &input) {
    if (title.exist(input)) {
        auto aux = title.search(input);

        std::vector<char> list;
    }
}

void Searcher::load(Trie &trie, const std::string &key) {
    const auto sub_df = df.get_data(key);

    std::ranges::for_each(sub_df, [&](const auto &e) {
        trie.insert(e);
    });
}
