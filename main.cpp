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
            return 4;
        default:
            return 0;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <expression>" << std::endl;
        return 1;
    }

    std::string problem = argv[1];

    std::vector<token> tokens = tokenize(problem);

    node* root;
    // Shunting yard algorithm with 2 stacks instead of 1 stack and 1 queue
    std::stack<token> ops;
    std::stack<node*> nodes;
    for (const token& t : tokens) {
        if (t.type == token_t::NUMBER) {
            nodes.push(new node(t));
        } else if (t.type == token_t::LPAREN) {
            ops.push(t);
        } else if (t.type == token_t::RPAREN) {
            while (!ops.empty() && ops.top().type != token_t::LPAREN) {
                node* right = nodes.top(); nodes.pop();
                node* left = (ops.top().type == token_t::SIN || ops.top().type == token_t::COS || ops.top().type == token_t::TAN) ? nullptr : nodes.top();
                if (left) nodes.pop();
                nodes.push(new node(ops.top(), left, right));
                ops.pop();
            }
            ops.pop(); // Pop the left parenthesis
        } else {
            while (!ops.empty() && precedence(t.type) <= precedence(ops.top().type)) {
                node* right = nodes.top(); nodes.pop();
                node* left = (ops.top().type == token_t::SIN || ops.top().type == token_t::COS || ops.top().type == token_t::TAN) ? nullptr : nodes.top();
                if (left) nodes.pop();
                nodes.push(new node(ops.top(), left, right));
                ops.pop();
            }
            ops.push(t);
        }
    }

    while (!ops.empty()) {
        if (nodes.size() < 2 && (ops.top().type != token_t::SIN && ops.top().type != token_t::COS && ops.top().type != token_t::TAN)) {
            std::cerr << "Error: not enough operands for operator " << ops.top().value << std::endl;
            return 1;
        }
        node* right = nodes.top(); nodes.pop();
        node* left = (ops.top().type == token_t::SIN || ops.top().type == token_t::COS || ops.top().type == token_t::TAN) ? nullptr : nodes.top();
        if (left) nodes.pop();
        nodes.push(new node(ops.top(), left, right));
        ops.pop();
    }

    root = nodes.top();

    float result = evaluate(root);

    std::cout << "Result: " << result << std::endl;

    return 0;
}
