//
// Created by tconto on 7/5/24.
//

#ifndef TREE_H
#define TREE_H

#include <utility>

#include "tokenizer.h"



struct node {
    token data;
    node* left;
    node* right;

    explicit node(token data, node* left = nullptr, node* right = nullptr)
        : data(std::move(data)), left(left), right(right) {}
};

float evaluate(node* root);

#endif //TREE_H
