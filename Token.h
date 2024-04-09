#pragma once
#include <stack>
#include <variant>

enum Operator {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
};

struct Operand {
    double value;
};

using TokenValue = std::variant<Operator, Operand>;

class Token {
public:
    [[nodiscard]] bool isOperand() const {
        return std::holds_alternative<Operand>(m_value);
    }
    TokenValue getValue() {
        return m_value;
    }
    explicit Token(Operator oprtr): m_value(oprtr) {}
    explicit Token(Operand oprnd): m_value(oprnd) {}
private:
    TokenValue m_value;
};