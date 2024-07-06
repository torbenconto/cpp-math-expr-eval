#include <iostream>
#include <stack>
#include <vector>
#include "tokenizer.h"
#include "tree.h"

auto precedence = [](token_t type) {
    switch (type) {
        case token_t::PLUS:
        case token_t::MINUS:
            return 1;
        case token_t::MULTIPLY:
        case token_t::DIVIDE:
            return 2;
        case token_t::EXPONENT:
            return 3;
        case token_t::SIN:
        case token_t::COS:
        case token_t::TAN:
        case token_t::SQRT:
        case token_t::LOG:
        case token_t::LOG_BASE:
        case token_t::ABS:
            return 4;
        default:
            return 0;
    }
};

bool isUnaryOperator(token_t type) {
    return type == token_t::SIN || type == token_t::COS || type == token_t::TAN ||
           type == token_t::SQRT || type == token_t::LOG || type == token_t::LOG_BASE || type == token_t::ABS;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <expression>" << std::endl;
        return 1;
    }

    std::string problem = argv[1];

    std::vector<token> tokens = tokenize(problem);

    node* root;
    std::stack<token> ops;
    std::stack<node*> nodes;

    for (const token& t : tokens) {
        if (t.type == token_t::NUMBER) {
            nodes.push(new node(t));
        } else if (t.type == token_t::LPAREN) {
            ops.push(t);
        } else if (t.type == token_t::RPAREN) {
            while (!ops.empty() && ops.top().type != token_t::LPAREN) {
                token op = ops.top();
                ops.pop();
                node* operand = nodes.top();
                nodes.pop();
                if (isUnaryOperator(op.type)) {
                    nodes.push(new node(op, nullptr, operand));
                } else {
                    node* left = nodes.top();
                    nodes.pop();
                    nodes.push(new node(op, left, operand));
                }
            }
            ops.pop(); // Pop the left parenthesis
        } else {
            while (!ops.empty() && precedence(t.type) <= precedence(ops.top().type)) {
                token op = ops.top();
                ops.pop();
                node* operand = nodes.top();
                nodes.pop();
                if (isUnaryOperator(op.type)) {
                    nodes.push(new node(op, nullptr, operand));
                } else {
                    node* left = nodes.top();
                    nodes.pop();
                    nodes.push(new node(op, left, operand));
                }
            }
            ops.push(t);
        }
    }

    while (!ops.empty()) {
        token op = ops.top();
        ops.pop();
        node* operand = nodes.top();
        nodes.pop();
        if (isUnaryOperator(op.type)) {
            nodes.push(new node(op, nullptr, operand));
        } else {
            node* left = nodes.top();
            nodes.pop();
            nodes.push(new node(op, left, operand));
        }
    }

    root = nodes.top();

    float result = evaluate(root);

    std::cout << "Result: " << result << std::endl;

    return 0;
}
