//
// Created by Bryan on 11/13/2024.
//

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>
#include <algorithm>
#include <ostream>

template<class TKey, class TValue>
class Dictionary {
    typedef std::vector<std::pair<TKey, TValue> > Collection;

public:
    const Collection &get_collection() const;

    const TKey &get_key(int index) const;

    int count() const;

    Dictionary() = default;

    Dictionary(const Dictionary &other);

    Dictionary(Dictionary &&other) noexcept;

    ~Dictionary() = default ;

    void add(const TKey &key, const TValue &value);

    void clear();

    auto contains_key(const TKey &key);

    void remove(const TKey &key);

    TValue &operator[](const TKey &key);

    Dictionary &operator=(const Dictionary &other);

    template<class K, class V>
    friend std::ostream &operator<<(std::ostream &os, const Dictionary<K, V> &other);

private:
    Collection collection;
};

template<class TKey, class TValue>
const typename
Dictionary<TKey, TValue>::Collection &Dictionary<TKey, TValue>::get_collection() const {
    return collection;
}

template<class TKey, class TValue>
const TKey &Dictionary<TKey, TValue>::get_key(int index) const {
    if (index >= count())
        throw std::out_of_range("The index does not exist in the dictionary");

    return collection[index].first;
}

template<class TKey, class TValue>
int Dictionary<TKey, TValue>::count() const {
    return collection.size();
}

template<class TKey, class TValue>
Dictionary<TKey, TValue>::Dictionary(const Dictionary &other): collection(other.get_collection()) {
}

template<class TKey, class TValue>
Dictionary<TKey, TValue>::Dictionary(Dictionary &&other) noexcept: collection(std::move(other.collection)) {
}

template<class TKey, class TValue>
void Dictionary<TKey, TValue>::add(const TKey &key, const TValue &value) {
    if (contains_key(key) == collection.end())
        collection.push_back({key, value});
}

template<class TKey, class TValue>
void Dictionary<TKey, TValue>::clear() {
    collection.clear();
}

template<class TKey, class TValue>
auto Dictionary<TKey, TValue>::contains_key(const TKey &key) {
    return std::ranges::find_if(collection.begin(), collection.end(), [&](const auto &e) {
        return key == e.first;
    });
}

template<class TKey, class TValue>
void Dictionary<TKey, TValue>::remove(const TKey &key) {
    auto it = contains_key(key);

    if (it != collection.end())
        collection.erase(it);
}

template<class TKey, class TValue>
TValue &Dictionary<TKey, TValue>::operator[](const TKey &key) {
    auto it = contains_key(key);

    if (it == collection.end())
        throw std::out_of_range("The key does not exist in the dictionary");

    return it->second;
}

template<class TKey, class TValue>
Dictionary<TKey, TValue> &Dictionary<TKey, TValue>::operator=(const Dictionary &other) {
    this->collection = other.collection;
    return *this;
}

inline std::ostream &operator <<(std::ostream &os, const std::vector<std::string> &other) {
    std::ranges::for_each(other, [&](const auto &item) {
        os << item << " ";
    });

    return os;
}

template<class TKey, class TValue>
std::ostream &operator<<(std::ostream &os, const Dictionary<TKey, TValue> &other) {
    std::ranges::for_each(other.collection, [&](const auto &e) {
        os
                << "[" << e.first << "]: "
                << "{" << e.second << "}"
                << std::endl;
    });
    return os;
}

#endif //DICTIONARY_H
