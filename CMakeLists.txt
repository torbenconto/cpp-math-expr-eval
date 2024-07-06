cmake_minimum_required(VERSION 3.28)
project(expr_eval)

set(CMAKE_CXX_STANDARD 26)

add_executable(expr_eval main.cpp
        tokenizer.cpp
        tokenizer.h
        tree.cpp
        tree.h)
