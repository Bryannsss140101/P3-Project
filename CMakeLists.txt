cmake_minimum_required(VERSION 3.29)
project(P3_Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(P3_Project main.cpp
        src/main/csv/Csv.cpp
        src/main/csv/Csv.h
        src/main/register/Register.h
        src/main/csv/DataFrame.cpp
        src/main/csv/DataFrame.h
        src/main/csv/Dictionary.h
)
