//
// Created by tconto on 7/5/24.
//

#include "tree.h"
#include <iostream>
#include <cmath>

float evaluate(node* root) {
    if (!root) {
        return 0;
    }

    if (root->data.type == token_t::NUMBER) {
        try {
            return std::stof(root->data.value);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << std::endl;
            return 0;
        }
    }

    float left = evaluate(root->left);
    float right = evaluate(root->right);

    switch (root->data.type) {
        case token_t::PLUS:
            return left + right;
        case token_t::MINUS:
            return left - right;
        case token_t::MULTIPLY:
            return left * right;
        case token_t::DIVIDE:
            if (right == 0) {
                std::cerr << "Division by zero error" << std::endl;
                return 0;
            }
        return left / right;
        case token_t::EXPONENT:
            return std::pow(left, right);
        case token_t::SIN:
            return std::sin(right);
        case token_t::COS:
            return std::cos(right);
        case token_t::TAN:
            return std::tan(right);
        case token_t::SQRT:
            return std::sqrt(right);
        case token_t::LOG:
            return std::log(right);
        case token_t::LOG_BASE:
            return std::log(right) / std::log(std::stof(root->data.value));
        case token_t::ABS:
            return std::abs(right);
        default:
            std::cerr << "Unknown token type" << std::endl;
        return 0;
    }
}