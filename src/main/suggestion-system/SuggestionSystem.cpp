//
// Created by Carlos on 3/12/2024.
//

#include <vector>
#include <string>
#include <sstream>
#include "../node/TrieNode.h"
#include "SuggestionSystem.h"

std::vector<std::string> SuggestionSystem::generate_suggestions() {
    std::vector<std::string> suggestions;
    generate_suggestions_helper(root_node, "", suggestions);
    return suggestions;
}

void SuggestionSystem::generate_suggestions_helper(
    TrieNode<char>* node,
    const std::string& prefix,
    std::vector<std::string>& suggestions) {

    if (node == nullptr) return;

    if (node->get_end()) {
        suggestions.push_back(prefix); // Agrega el prefijo actual si es una palabra completa
    }

    for (const auto& [key, child_node] : node->get_nodes()) {
        generate_suggestions_helper(child_node, prefix + key, suggestions);
    }
}

std::vector<std::string> search_with_prefix(Trie& tree, const std::string& prefix) {
    TrieNode<char>* node = tree.search(prefix);
    std::vector<std::string> suggestions;

    if (node) {
        SuggestionSystem suggestion_system(node);
        suggestions = suggestion_system.generate_suggestions();
    }

    return suggestions;
}

std::vector<std::string> search_with_phrase(Trie& tree, const std::string& phrase) {
    std::istringstream stream(phrase);
    std::string word;
    std::vector<std::string> results;

    while (stream >> word) {
        std::vector<std::string> temp_results = search_with_prefix(tree, word);
        results.insert(results.end(), temp_results.begin(), temp_results.end());
    }

    return results;
}