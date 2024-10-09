#include <iostream>
#include <string>
using namespace std;


void tokenizer(const string& problem){
    for(size_t i = 0; i < problem.size(); i++){
        char currentChar = problem[i];

        switch (currentChar)
        {
            case (isdigit(currentChar)):
            
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

    cout << problem;
}