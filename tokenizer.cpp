//
// Created by tconto on 7/5/24.
//

#include "tokenizer.h"

#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>

std::vector<token> tokenize(const std::string& input) {
    std::vector<token> tokens;
    std::string number;

    std::unordered_map<char, token_t> charToToken = {
        {'+', token_t::PLUS},
        {'-', token_t::MINUS},
        {'*', token_t::MULTIPLY},
        {'^', token_t::EXPONENT},
        {'/', token_t::DIVIDE},
        {'(', token_t::LPAREN},
        {')', token_t::RPAREN}
    };

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
        if (std::isdigit(c)) {
            number += c;
        } else {
            if (!number.empty()) {
                tokens.push_back({token_t::NUMBER, number});
                number.clear();
            }

            if (charToToken.count(c)) {
                tokens.push_back({charToToken[c], std::string(1, c)});
            } else if (c == 's' && input.substr(i, 3) == "sin") {
                tokens.push_back({token_t::SIN, "sin"});
                i += 2;
            } else if (c == 'c' && input.substr(i, 3) == "cos") {
                tokens.push_back({token_t::COS, "cos"});
                i += 2;
            } else if (c == 't' && input.substr(i, 3) == "tan") {
                tokens.push_back({token_t::TAN, "tan"});
                i += 2;
            } else if (!std::isspace(c)) {
                tokens.push_back({token_t::UNKNOWN, std::string(1, c)});
            }
        }
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