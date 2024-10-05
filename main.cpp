#include <iostream>
#include <cmath>

double getNumber(){
    double number;
    std::cout << "Enter number: ";
    std::cin >> number;
    return number;
}
char getOperation(){
    char operation;
    std::cout << "Enter operation: ";
    std::cin >> operation;
    return operation;
}
double operate(double num1, double num2, char operation){
    //operates on the values based on the current operation 
    //entered and the numbers in consideration
    switch(operation){
        case '+':
            return num1 + num2;
            break;
        case '-':
            return num1 - num2;
            break;
        case '*':
            return num1 * num2;
            break;
        case '/':
            if (num2 != 0){
                return num1 / num2;
            } else{
                std::cerr << "Division by zero error!" << std::endl;
                return 0;
            }
            break;
        default:
            std::cerr << "Invalid operator!";
            return 0;
    }
}

int main(){
    std::cout << "___________________Command line Calculator App!___________________\n";
    std::cout << "Enter your numbers and operations. Enter the '=' for the results.\n";
    char operation;
    double num1{0};
    double num2{0};
    double output{num1};

    while(operation != '='){
        num1 = getNumber();
        output = num1; // assign output to the first enterd number
        operation = getOperation();
        std::cout << "output: " << output << " operation: " << operation << std::endl; // for debuging
        num2 = getNumber();
        output = operate(num1, num2, operation);
        operation = getOperation();
        std::cout << "output: " << output << " operation: " << operation << std::endl; // for debuging
    };
    std::cout << "Answer: " << output << std::endl;
    return 0;
}