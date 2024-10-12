#include <iostream>
#include <vector>
#include <string>
using namespace std;


 vector<string> tokenizer(const string& problem){
    string number = "";
    bool decimalAdded{false};
    vector<string> tokens;


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
                tokens.push_back(number); 
                number = "";
                decimalAdded = false;
            }
            tokens.push_back(string(1, currentChar));// Line 38
        }
    }
    // add the final token
    if (number != ""){
        tokens.push_back(number);
    }

    // // loop through the vector
    // for(size_t i = 0; i < tokens.size(); i++){
    //     cout << tokens[i] << endl;
    // }
    return tokens;
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