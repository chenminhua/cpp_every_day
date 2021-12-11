#include <string>
#include <iostream>
using namespace std; // strings 也在这个 namespace下面

int main() {
    string myString = "hello";
    string otherString = "world";

    cout << myString + otherString << endl;

    myString.append(", ");
    cout << myString + otherString << endl;

    string str = "hello, cpp language";
    cout << str.substr(7,3) << endl;
}

