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
    Collection get_data() const;

    int count() const;

    Dictionary() = default;

    Dictionary(const Dictionary &other);

    Dictionary(Dictionary &&other) noexcept;

    ~Dictionary() = default ;

    void add(TKey key, TValue value);

    void clear();

    auto contains_key(TKey key);

    void remove(TKey key);

    TValue &operator[](const TKey &key);

    template<class K, class V>
    friend std::ostream &operator<<(std::ostream &os, const Dictionary<K, V> &other);

private:
    Collection data;
};

template<class TKey, class TValue>
typename Dictionary<TKey, TValue>::Collection Dictionary<TKey, TValue>::get_data() const {
    return data;
}

template<class TKey, class TValue>
int Dictionary<TKey, TValue>::count() const {
    return data.size();
}

template<class TKey, class TValue>
Dictionary<TKey, TValue>::Dictionary(const Dictionary &other): data(other.get_data()) {
}

template<class TKey, class TValue>
Dictionary<TKey, TValue>::Dictionary(Dictionary &&other) noexcept: data(std::move(other.data)) {
}

template<class TKey, class TValue>
void Dictionary<TKey, TValue>::add(TKey key, TValue value) {
    if (contains_key(key) == data.end())
        data.push_back({key, value});
}

template<class TKey, class TValue>
void Dictionary<TKey, TValue>::clear() {
    data.clear();
}

template<class TKey, class TValue>
auto Dictionary<TKey, TValue>::contains_key(TKey key) {
    return std::ranges::find_if(data.begin(), data.end(), [&](const auto &e) {
        return key == e.first;
    });
}

template<class TKey, class TValue>
void Dictionary<TKey, TValue>::remove(TKey key) {
    auto it = contains_key(key);

    if (it != data.end())
        data.erase(it);
}

template<class TKey, class TValue>
TValue &Dictionary<TKey, TValue>::operator[](const TKey &key) {
    auto it = contains_key(key);

    if (it == data.end())
        throw std::out_of_range("The key does not exist in the dictionary");

    return it->second;
}

inline std::ostream &operator <<(std::ostream &os, const std::vector<std::string> &other) {
    std::ranges::for_each(other, [&](const auto &item) {
        os << item << " ";
    });

    return os;
}

template<class TKey, class TValue>
std::ostream &operator<<(std::ostream &os, const Dictionary<TKey, TValue> &other) {
    std::ranges::for_each(other.data, [&](const auto &e) {
        os
                << "[" << e.first << "]: "
                << "{" << e.second << "}"
                << std::endl;
    });
    return os;
}

#endif //DICTIONARY_H
