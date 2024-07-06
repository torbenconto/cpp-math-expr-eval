//
// Created by tconto on 7/5/24.
//

#include "tokenizer.h"

#include <string>
#include <vector>
#include <cctype>

std::vector<token> tokenize(const std::string& input) {
    std::vector<token> tokens;
    std::string number;

    for (char c : input) {
        if (std::isdigit(c)) {
            number += c;
        } else {
            if (!number.empty()) {
                tokens.push_back({token_t::NUMBER, number});
                number.clear();
            }

            switch (c) {
                case '+':
                    tokens.push_back({token_t::PLUS, "+"});
                break;
                case '-':
                    tokens.push_back({token_t::MINUS, "-"});
                break;
                case '*':
                    tokens.push_back({token_t::MULTIPLY, "*"});
                break;
                case '/':
                    tokens.push_back({token_t::DIVIDE, "/"});
                break;
                case '(':
                    tokens.push_back({token_t::LPAREN, "("});
                break;
                case ')':
                    tokens.push_back({token_t::RPAREN, ")"});
                break;
                default:
                    if (!std::isspace(c)) {
                        tokens.push_back({token_t::UNKNOWN, std::string(1, c)});
                    }
                break;
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
        case token_t::UNKNOWN:
            default:
                return "UNKNOWN";
    }
}