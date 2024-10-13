#include <iostream>
#include <vector>
#include <string>
#include <memory>   // For smart pointers
#include <stdexcept> // For exception handling

using namespace std;

// Token Types
enum class TokenType { NUMBER, OPERATOR, PARENTHESIS };

// Token Class
class Token {
public:
    TokenType type;
    string value;

    Token(TokenType t, const string& v) : type(t), value(v) {}
};

// Base class for AST Nodes
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual double evaluate() const = 0; // Pure virtual function for evaluation
};

// Number Node: Leaf node that holds a number
class NumberNode : public ASTNode {
private:
    double value;

public:
    NumberNode(double v) : value(v) {}
    
    double evaluate() const override {
        return value;
    }
};

// Operator Node: Internal node that holds an operator and two children
class OperatorNode : public ASTNode {
private:
    char op;
    unique_ptr<ASTNode> left;
    unique_ptr<ASTNode> right;

public:
    OperatorNode(char oper, unique_ptr<ASTNode> l, unique_ptr<ASTNode> r)
        : op(oper), left(move(l)), right(move(r)) {}

    double evaluate() const override {
        double leftValue = left->evaluate();
        double rightValue = right->evaluate();

        switch (op) {
            case '+': return leftValue + rightValue;
            case '-': return leftValue - rightValue;
            case '*': return leftValue * rightValue;
            case '/': 
                if (rightValue == 0) throw runtime_error("Division by zero");
                return leftValue / rightValue;
            default: throw runtime_error("Unknown operator");
        }
    }
};

// Tokenizer: Converts a string into tokens
vector<Token> tokenizer(const string& problem) {
    vector<Token> tokens;
    string number = "";
    bool decimalAdded = false;

    for (size_t i = 0; i < problem.size(); ++i) {
        char currentChar = problem[i];

        if (isdigit(currentChar)) {
            number += currentChar;
        } 
        else if (currentChar == '.') {
            if (!decimalAdded) {
                number += currentChar;
                decimalAdded = true;
            } 
            else {
                throw runtime_error("Invalid input: multiple decimals in a number");
            }
        } 
        else {
            // Push number token if there is one accumulated
            if (!number.empty()) {
                tokens.emplace_back(TokenType::NUMBER, number);
                number = "";
                decimalAdded = false;
            }

            // Handle operators and parentheses
            if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
                tokens.emplace_back(TokenType::OPERATOR, string(1, currentChar));
            } 
            else if (currentChar == '(' || currentChar == ')') {
                tokens.emplace_back(TokenType::PARENTHESIS, string(1, currentChar));
            }
        }
    }

    // Push the last number if any
    if (!number.empty()) {
        tokens.emplace_back(TokenType::NUMBER, number);
    }

    return tokens;
}

// Parser: Converts tokens into an AST
unique_ptr<ASTNode> parseExpression(const vector<Token>& tokens, size_t& index);
unique_ptr<ASTNode> parseTerm(const vector<Token>& tokens, size_t& index);
unique_ptr<ASTNode> parseFactor(const vector<Token>& tokens, size_t& index);

// Helper to check operator precedence
int precedence(const string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

// Parse expression: Handles addition and subtraction
unique_ptr<ASTNode> parseExpression(const vector<Token>& tokens, size_t& index) {
    auto left = parseTerm(tokens, index);

    while (index < tokens.size() && tokens[index].type == TokenType::OPERATOR && 
           (tokens[index].value == "+" || tokens[index].value == "-")) {
        char op = tokens[index].value[0];
        ++index; // Move past the operator
        auto right = parseTerm(tokens, index);
        left = make_unique<OperatorNode>(op, move(left), move(right));
    }

    return left;
}

// Parse term: Handles multiplication and division
unique_ptr<ASTNode> parseTerm(const vector<Token>& tokens, size_t& index) {
    auto left = parseFactor(tokens, index);

    while (index < tokens.size() && tokens[index].type == TokenType::OPERATOR && 
           (tokens[index].value == "*" || tokens[index].value == "/")) {
        char op = tokens[index].value[0];
        ++index; // Move past the operator
        auto right = parseFactor(tokens, index);
        left = make_unique<OperatorNode>(op, move(left), move(right));
    }

    return left;
}

// Parse factor: Handles numbers and parentheses
unique_ptr<ASTNode> parseFactor(const vector<Token>& tokens, size_t& index) {
    if (tokens[index].type == TokenType::NUMBER) {
        double value = stod(tokens[index].value);
        ++index; // Move past the number
        return make_unique<NumberNode>(value);
    } 
    else if (tokens[index].value == "(") {
        ++index; // Move past the '('
        auto node = parseExpression(tokens, index);
        if (tokens[index].value != ")") {
            throw runtime_error("Mismatched parentheses");
        }
        ++index; // Move past the ')'
        return node;
    } 
    else {
        throw runtime_error("Unexpected token");
    }
}

// Main function: Tokenize, parse, and evaluate
int main() {
    cout << "___________________Command line Calculator!___________________\n";
    string problem;

    cout << "Enter the problem: ";
    getline(cin, problem);

    // Tokenize the input
    vector<Token> tokens = tokenizer(problem);

    // Parse the tokens into an AST
    size_t index = 0;
    unique_ptr<ASTNode> ast = parseExpression(tokens, index);

    // Evaluate the AST
    try {
        double result = ast->evaluate();
        cout << "Result: " << result << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
