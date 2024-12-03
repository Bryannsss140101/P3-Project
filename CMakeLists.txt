cmake_minimum_required(VERSION 3.29)
project(P3_Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(P3_Project main.cpp
        src/main/csv/Csv.cpp
        src/main/csv/Csv.h
        src/main/dataframe/DataFrame.cpp
        src/main/dataframe/DataFrame.h
        src/main/Dictionary/Dictionary.h
        src/main/trie/Trie.cpp
        src/main/trie/Trie.h
        src/main/node/TrieNode.h
        src/main/suggestion-system/SuggestionSystem.cpp
        src/main/suggestion-system/SuggestionSystem.h

)
