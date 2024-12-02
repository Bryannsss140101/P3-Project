//
// Created by Bryan on 11/26/2024.
//

#ifndef NODE_H
#define NODE_H
#include <unordered_map>
#include <algorithm>

template<class T>
class TrieNode {
public:
    void set_end(const bool is_end) { end = is_end; }
    bool get_end() const { return end; }
    auto get_nodes() { return nodes; }

    explicit TrieNode()
        : nodes(std::unordered_map<T, TrieNode *>()), end(false) {
    }

    ~TrieNode() {
        std::ranges::for_each(nodes, [](const auto &e) {
            delete e.second;
        });
    }

    TrieNode *&get_node(const T &key) {
        return nodes[key];
    }

    bool exist(const T &key) {
        return nodes.contains(key);
    }

    void push(const T &key, TrieNode *value) {
        nodes.insert({key, value});
    }

private:
    std::unordered_map<T, TrieNode *> nodes;
    bool end;
};

#endif //NODE_H
