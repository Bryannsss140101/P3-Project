//
// Created by Bryan on 11/24/2024.
//

#ifndef BST_H
#define BST_H

template<class T>
struct Node {
    T data;
    Node *right;
    Node *left;

    explicit Node(T data)
        : data(data), right(nullptr), left(nullptr) {
    }
};

template<class T>
class BST {
public:
    Node<T> *root;

    BST();

    ~BST();

    int size();

    void insert(const T &data);

    Node<T> *search(const T &data);

private:
    int size_tree(const Node<T> *node);

    Node<T> *insert_node(Node<T> *node, const T &data);

    Node<T> *search_node(Node<T> *node, const T &data);
};

template<class T>
BST<T>::BST(): root(nullptr) {
}

template<class T>
BST<T>::~BST() {
    delete root;
}

template<class T>
int BST<T>::size() {
    return size_tree(root);
}

template<class T>
void BST<T>::insert(const T &data) {
    root = insert_node(root, data);
}

template<class T>
Node<T> *BST<T>::search(const T &data) {
    return search_node(root, data);
}

template<class T>
int BST<T>::size_tree(const Node<T> *node) {
    if (node == nullptr)
        return 0;
    return 1 + size_tree(node->left) + size_tree(node->right);
}

template<class T>
Node<T> *BST<T>::insert_node(Node<T> *node, const T &data) {
    if (node == nullptr)
        return new Node<T>(data);

    if (data < node->data)
        node->left = insert_node(node->left, data);
    else
        node->right = insert_node(node->right, data);
    return node;
}

template<class T>
Node<T> *BST<T>::search_node(Node<T> *node, const T &data) {
    if (node == nullptr || node->data == data)
        return node;

    if (data < node->data)
        return search_node(node->left, data);
    return search_node(node->right, data);
}

#endif //BST_H
