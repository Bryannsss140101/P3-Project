//
// Created by Bryan on 11/26/2024.
//

#include "Trie.h"

TrieNode<char> *Trie::get_root() const {
    return root;
}

Trie::Trie() : root(new TrieNode<char>{}) {
}

Trie::~Trie() {
    delete root;
}

void Trie::insert(const std::string &word) {
    root = insert(root, word);
}

TrieNode<char> *Trie::search(const std::string &word) {
    return search(root, word);
}

bool Trie::exist(const std::string &word) {
    return search(root, word);
}

TrieNode<char> *Trie::insert(TrieNode<char> *trie_node, const std::string &word) {
    if (word.empty()) {
        trie_node->set_end(true);
        return trie_node;
    }

    const auto c = word[0];
    trie_node->push(c, new TrieNode<char>{});
    trie_node->get_node(c) = insert(trie_node->get_node(c), word.substr(1));

    return trie_node;
}

TrieNode<char> *Trie::search(TrieNode<char> *trie_node, const std::string &word) {
    if (trie_node == nullptr || word.empty())
        return trie_node;

    const auto c = word[0];

    return search(trie_node->get_node(c), word.substr(1));
}
