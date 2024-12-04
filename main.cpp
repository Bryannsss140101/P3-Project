#include <iostream>
#include <conio.h>
#include <unordered_map>
#include "src/main/trie/Trie.h"

#include "src/main/csv/Csv.h"
#include "src/main/dataframe/DataFrame.h"
#include "src/main/searcher/Searcher.h"
#include "src/main/suggestion-system/SuggestionSystem.h"

using namespace std;

int main() {
    Searcher searcher("mpst_full_data.csv");

    searcher.find("Scar");

    for (auto s = searcher.get_suggestions(); const auto &e: s) {
        cout << s << endl;
    }


    _getch();

    return 0;
}
