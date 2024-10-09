#include <iostream>
#include <string>
using namespace std;


void tokenizer(const string& problem){
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
        // check for whitespace
        else if (currentChar == ' '){
            cout << "whitespace\n";
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