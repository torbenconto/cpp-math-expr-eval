//
// Created by tconto on 7/5/24.
//

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

enum class token_t {
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    UNKNOWN,
};

struct token {
    token_t type;
    std::string value;
};

std::vector<token> tokenize(const std::string& expression);
std::string tokenTypeToString(token_t type);


#endif //TOKENIZER_H
