#pragma once
#include <stack>
#include <queue>
#include <variant>
#include "Token.h"
#include <string>
#include <map>

class Calculator {
public:
    double calculate(const std::string& input);
private:
    std::stack<Operator> stack;
    std::queue<Token> postfix;
    std::string bufferNumber;
    void pushToStack(Operator oprtr);
    void handleBufferNumber();
    std::map<Operator, int> priorityMap = {
            {Operator::ADD, 1},
            {Operator::SUBTRACT, 1},
            {Operator::DIVIDE, 2},
            {Operator::MULTIPLY, 2}
    };
};

double Calculator::calculate(const std::string& input) {
    for (char c: input) {
        if(isdigit(c)) {
            bufferNumber += c;
        } else {
            handleBufferNumber();
            switch (c) {
                case '+':
                    pushToStack(ADD);
                    break;
                case '-':
                    pushToStack(SUBTRACT);
                    break;
                case '*':
                    pushToStack(MULTIPLY);
                    break;
                case '/':
                    pushToStack(DIVIDE);
                    break;
                default:
                    break;
            }
        }
    }
    handleBufferNumber();
    while (!stack.empty()) {
        postfix.push(Token(stack.top()));
        stack.pop();
    }
    std::stack<double> numbers;
    while (!postfix.empty()) {
        if (postfix.front().isOperand()) {
            Operand oprnd = std::get<Operand>(postfix.front().getValue());
            numbers.push(oprnd.value);
            postfix.pop();
        } else {
            double b = numbers.top();
            numbers.pop();
            double a = numbers.top();
            numbers.pop();
            Operator oprtr = std::get<Operator>(postfix.front().getValue());
            double value;

            switch (oprtr) {
                case ADD:
                    value = a + b;
                    break;
                case SUBTRACT:
                    value = a - b;
                    break;
                case MULTIPLY:
                    value = a * b;
                    break;
                case DIVIDE:
                    value = a / b;
                    break;
            }
            numbers.push(value);
            postfix.pop();
        }
    }
    return numbers.top();
}

void Calculator::pushToStack(Operator oprtr) {
    while (!stack.empty() && priorityMap.at(oprtr) <= priorityMap.at(stack.top())) {
        postfix.push(Token(stack.top()));
        stack.pop();
    }
    stack.push(oprtr);
}

void Calculator::handleBufferNumber() {
    if (!bufferNumber.empty()) {
        Operand operand{};
        operand.value = std::stod(bufferNumber);
        Token token(operand);
        postfix.push(token);
        bufferNumber = "";
    }
}
