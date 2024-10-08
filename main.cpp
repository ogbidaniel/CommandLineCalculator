#include <iostream>
#include <string>
using namespace std;

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