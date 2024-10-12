#include <iostream>
#include <string>
using namespace std;


void tokenizer(const string& problem){
    char dig[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
    char opp[4] = {'+', '-', '*', '/'};
    char par[2] = {'(', ')'};
    string number = "";
    bool decimalAdded{false};


    for(size_t i = 0; i < problem.size(); i++){
        char currentChar = problem[i];

        // check for digit
        if (isdigit(currentChar)){
            number = number + currentChar;
        }
        // check decimal
        else if (currentChar == '.'){
            if (decimalAdded == false){
                number = number + currentChar;
                decimalAdded = true;
            }
            else{
                cout << "Error in input problem\n";
                return;
            }
        }
        // end accumulator and print out other parts of the problem
        else{
            if (number != ""){
                cout << number << endl;
                number = "";
                decimalAdded = false;
            }
            cout << currentChar << endl;
        }
    }
    // print the final token
    if (number != ""){
        cout << number << endl;
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