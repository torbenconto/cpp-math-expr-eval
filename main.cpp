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
        default:
            return 0;
    }
};

int main() {
    std::string problem = "4 * ( 5 - 6 )"; // -4

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
                node* left = nodes.top(); nodes.pop();
                nodes.push(new node(ops.top(), left, right));
                ops.pop();
            }
            ops.pop(); // Pop the left parenthesis
        } else {
            while (!ops.empty() && precedence(t.type) <= precedence(ops.top().type)) {
                node* right = nodes.top(); nodes.pop();
                node* left = nodes.top(); nodes.pop();
                nodes.push(new node(ops.top(), left, right));
                ops.pop();
            }
            ops.push(t);
        }
    }

    while (!ops.empty()) {
        node* right = nodes.top(); nodes.pop();
        node* left = nodes.top(); nodes.pop();
        nodes.push(new node(ops.top(), left, right));
        ops.pop();
    }

    root = nodes.top();

    float result = evaluate(root);

    std::cout << "Result: " << result << std::endl;

    return 0;
}
