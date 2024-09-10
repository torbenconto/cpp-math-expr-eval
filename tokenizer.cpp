//
// Created by tconto on 7/5/24.
//

#include "tokenizer.h"

#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>
#include <iostream>


std::vector<token> tokenize(const std::string& input) {
    std::vector<token> tokens;
    std::string number;

    if (input.empty()) {
        return tokens;
    }

    std::unordered_map<char, token_t> charToToken = {
        {'+', token_t::PLUS},
        {'-', token_t::MINUS},
        {'*', token_t::MULTIPLY},
        {'^', token_t::EXPONENT},
        {'/', token_t::DIVIDE},
        {'(', token_t::LPAREN},
        {')', token_t::RPAREN}
    };

    size_t i = 0;
    while (i < input.size()) {
        char c = input[i];

        if (std::isdigit(c) || (c == '-' && i + 1 < input.size() && std::isdigit(input[i + 1]))) {
            number += c;
        } else {
            if (!number.empty()) {
                tokens.push_back({token_t::NUMBER, number});
                number.clear();
            }

            // Handle implied multiplication between numbers and parentheses
            if (c == '(') {
                if (i > 0 && (std::isdigit(input[i - 1]) || input[i - 1] == ')')) {
                    tokens.push_back({token_t::MULTIPLY, "*"});
                }
                tokens.push_back({token_t::LPAREN, "("});
            } else if (c == ')') {
                tokens.push_back({token_t::RPAREN, ")"});
                if (i + 1 < input.size() && (std::isdigit(input[i + 1]) || input[i + 1] == '(')) {
                    tokens.push_back({token_t::MULTIPLY, "*"});
                }
            } else if (charToToken.count(c)) {
                tokens.push_back({charToToken[c], std::string(1, c)});
            } else if (c == 's' && i + 2 < input.size() && input.substr(i, 3) == "sin") {
                tokens.push_back({token_t::SIN, "sin"});
                i += 2;
            } else if (c == 'c' && i + 2 < input.size() && input.substr(i, 3) == "cos") {
                tokens.push_back({token_t::COS, "cos"});
                i += 2;
            } else if (c == 't' && i + 2 < input.size() && input.substr(i, 3) == "tan") {
                tokens.push_back({token_t::TAN, "tan"});
                i += 2;
            } else if (c == 's' && i + 3 < input.size() && input.substr(i, 4) == "sqrt") {
                tokens.push_back({token_t::SQRT, "sqrt"});
                i += 3;
            } else if (c == 'l' && i + 2 < input.size()) {
                if (input.substr(i, 3) == "log") {
                    if (i + 3 < input.size() && std::isdigit(input[i + 3])) {
                        std::string base;
                        i += 3;
                        while (i < input.size() && std::isdigit(input[i])) {
                            base += input[i++];
                        }
                        --i; // Roll back the last increment
                        tokens.push_back({token_t::LOG_BASE, base});
                    } else {
                        tokens.push_back({token_t::LOG, "log"});
                        i += 2;
                    }
                }
            } else if (c == 'a' && i + 2 < input.size() && input.substr(i, 3) == "abs") {
                tokens.push_back({token_t::ABS, "abs"});
                i += 2;
            } else if (!std::isspace(c)) {
                tokens.push_back({token_t::UNKNOWN, std::string(1, c)});
            }
        }
        ++i;
    }

    if (!number.empty()) {
        tokens.push_back({token_t::NUMBER, number});
    }

    return tokens;
}
std::string tokenTypeToString(token_t type) {
    switch (type) {
        case token_t::NUMBER:
            return "NUMBER";
        case token_t::PLUS:
            return "PLUS";
        case token_t::MINUS:
            return "MINUS";
        case token_t::MULTIPLY:
            return "MULTIPLY";
        case token_t::DIVIDE:
            return "DIVIDE";
        case token_t::LPAREN:
            return "LPAREN";
        case token_t::RPAREN:
            return "RPAREN";
        case token_t::EXPONENT:
            return "EXPONENT";
        case token_t::SIN:
            return "SIN";
        case token_t::COS:
            return "COS";
        case token_t::TAN:
            return "TAN";
        case token_t::UNKNOWN:
            default:
                return "UNKNOWN";
    }
}