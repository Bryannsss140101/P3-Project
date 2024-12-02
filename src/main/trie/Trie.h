//
// Created by Bryan on 11/26/2024.
//

#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <iostream>
#include "../node/TrieNode.h"

class Trie {
public:
    TrieNode<char>* get_root() const;

    Trie();

    ~Trie();

    void insert(const std::string &word);

    TrieNode<char> *search(const std::string &word);

    bool exist(const std::string &word);

private:
    TrieNode<char> *root;

    TrieNode<char> *insert(TrieNode<char> *trie_node, const std::string &word);

    TrieNode<char> *search(TrieNode<char> *trie_node, const std::string &word);
};

#endif //TRIE_H
