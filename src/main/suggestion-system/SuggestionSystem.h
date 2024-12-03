//
// Created by Carlos on 3/12/2024.
//

#ifndef SUGGESTIONSYSTEM_H
#define SUGGESTIONSYSTEM_H
#include <string>
#include <vector>
#include "../node/TrieNode.h"
#include "../trie/Trie.h"

class SuggestionSystem {
public:
    SuggestionSystem(TrieNode<char>* root_node)
        : root_node(root_node) {}

    std::vector<std::string> generate_suggestions();

private:
    TrieNode<char>* root_node;

    // Función recursiva para generar sugerencias
    static void generate_suggestions_helper(TrieNode<char>* node, const std::string& prefix, std::vector<std::string>& suggestions);
};

std::vector<std::string> search_with_prefix(Trie& trie, const std::string& prefix);
std::vector<std::string> search_with_phrase(Trie& trie, const std::string& phrase);


#endif //S// UGGESTIONSYSTEM_H
