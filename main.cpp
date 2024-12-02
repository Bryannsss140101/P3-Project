#include <iostream>
#include <conio.h>
#include <unordered_map>
#include "src/main/trie/Trie.h"

#include "src/main/csv/Csv.h"
#include "src/main/dataframe/DataFrame.h"

using namespace std;

int main() {
    /*auto csv = Csv("mpst_full_data.csv");
    csv.read_csv();
    auto df = csv.get_dataframe();

    cout << df.get_data() << endl;*/

    Trie tree;

    tree.insert("ap");
    tree.insert("apt");
    tree.insert("apto");
    tree.insert("aptitud");
    tree.insert("persa");
    tree.insert("perro");
    tree.insert("pedro");

    tree.DFS("a");

    _getch();

    return 0;
}
