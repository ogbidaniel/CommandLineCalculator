#include <iostream>
#include <string>
using namespace std;


void tokenizer(const string& problem){
    char dig[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
    for(size_t i = 0; i < problem.size(); i++){
        char currentChar = problem[i];

        // check for digit
        if (isdigit(currentChar)){
            cout << "digit: " << currentChar << "\n";
        }
        // check for operator
        else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/'){
            cout << "operator: " << currentChar << "\n";
        }
        // check for parentheses
        else if (currentChar == '(' || currentChar == ')'){
            cout << "parenthesis: " << currentChar << "\n";
        }
        // ignore whitespaces
        else if (isspace(currentChar)){
            continue;
        }

        // check for decimal
        else if (currentChar == '.'){
            cout << "decimal: " << currentChar << "\n";
        }   

        // unknown char
        else{
            cout << "unknown\n";
        }
        
        

    }
}

int main(){
    cout << "___________________Command line Calculator!___________________\n";
    bool notActive{false};
    string problem;
    
    while(notActive == false){
        cout << "Enter the problem: ";
        getline(cin, problem);
        notActive = true;
    }

    tokenizer(problem);

    return 0;
}