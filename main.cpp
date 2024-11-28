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

    tree.insert("apple");
    tree.insert("app");
    tree.insert("bat");
    tree.insert("ball");
    tree.insert("batman");
    tree.insert("balloon");
    tree.insert("cat");
    tree.insert("dog");

    cout << "Busqueda 'apple': " << (tree.search("apple") ? "Encontrado" : "No encontrado") << endl;
    cout << "Busqueda 'app': " << (tree.search("app") ? "Encontrado" : "No encontrado") << endl;
    cout << "Busqueda 'bat': " << (tree.search("bat") ? "Encontrado" : "No encontrado") << endl;
    cout << "Busqueda 'ball': " << (tree.search("ball") ? "Encontrado" : "No encontrado") << endl;
    cout << "Busqueda 'batman': " << (tree.search("batman") ? "Encontrado" : "No encontrado") << endl;
    cout << "Busqueda 'balloon': " << (tree.search("balloon") ? "Encontrado" : "No encontrado") << endl;
    cout << "Busqueda 'cat': " << (tree.search("cat") ? "Encontrado" : "No encontrado") << endl;
    cout << "Busqueda 'dog': " << (tree.search("dog") ? "Encontrado" : "No encontrado") << endl;
    cout << "Busqueda 'banana': " << (tree.search("banana") ? "Encontrado" : "No encontrado") << endl;

    _getch();

    return 0;
}
