#include <iostream>
#include <conio.h>
#include <unordered_map>
#include "src/main/trie/Trie.h"

#include "src/main/csv/Csv.h"
#include "src/main/dataframe/DataFrame.h"

#include <iostream>
#include <vector>
#include <conio.h>
#include "src/main/suggestion-system/SuggestionSystem.h"
#include "src/main/trie/Trie.h"
using namespace std;

int main() {
    string a;
    cout<<"Ingrese la palabra: "<<endl;
    cin>>a;

    Trie titulo;
    Trie sinopsis;

    // Insertar palabras en el Trie "titulo"
    titulo.insert("barco");
    titulo.insert("el barco fantasma");
    titulo.insert("el barco del Titanic");
    titulo.insert("el barco niño");
    titulo.insert("el barco fantastico");
    titulo.insert("el barco god");
    titulo.insert("barco gris");
    titulo.insert("barco gaaaa");

    // Insertar palabras en el Trie "sinopsis"
    sinopsis.insert("barco");
    sinopsis.insert("el barco carlos");
    sinopsis.insert("barco Super");
    sinopsis.insert("barco Adios");

    // Búsqueda en "titulo"
    TrieNode<char>* T = titulo.search(a);
    std::cout << "Dirección de 'barco' en titulo: " << T << std::endl;

    SuggestionSystem suggestion_system(T);
    std::vector<std::string> suggestions = suggestion_system.generate_suggestions();

    for (const auto& suggestion : suggestions)
        std::cout << "Sugerencias para "<<a<<" en el titulo:  " <<a<<" "<<suggestion << std::endl;

    // Búsqueda en "sinopsis"
    TrieNode<char>* S = sinopsis.search("barco");
    std::cout << "\nDirección de 'barco' en sinopsis: " << S << std::endl;

    SuggestionSystem suggestion_system2(S);
    std::vector<std::string> suggestions2 = suggestion_system2.generate_suggestions();

    for (const auto& suggestion : suggestions2)
        std::cout << "Sugerencias para 'barco' en sinopsis: " << suggestion << std::endl;

    std::cout<<std::endl;
    _getch();
    return 0;
}