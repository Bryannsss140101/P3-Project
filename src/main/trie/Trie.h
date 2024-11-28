//
// Created by Bryan on 11/26/2024.
//

#ifndef TRIE_H
#define TRIE_H

#include <string>

#include "../node/TrieNode.h"

class Trie {
public:
    Trie();

    ~Trie();

    void insert(const std::string &word);

    bool search(const std::string &word);

private:
    TrieNode<char> *root;

    TrieNode<char> *insert_node(TrieNode<char> *trie_node, const std::string &word);

    TrieNode<char> *search_node(TrieNode<char> *trie_node, const std::string &word);
};

#endif //TRIE_H
