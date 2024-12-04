//
// Created by Bryannsss.
//

#include "Searcher.h"
#include <algorithm>

std::vector<std::string> Searcher::get_suggestions() {
    return suggestions;
}

Searcher::Searcher(const std::string &file) {
    auto csv = Csv(file);
    csv.read_csv();
    df = csv.get_dataframe();
    load(title, "title");
}

void Searcher::find(const std::string &input) {
    if (title.exist(input)) {
        const auto aux = title.search(input);
        SuggestionSystem suggestion_system(aux);
        suggestions = suggestion_system.generate_suggestions(input);
    }
}

void Searcher::load(Trie &trie, const std::string &key) {
    const auto sub_df = df.get_data(key);

    std::ranges::for_each(sub_df, [&](const auto &e) {
        trie.insert(e);
    });
}
