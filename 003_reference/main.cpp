#include<iostream>
using namespace std;

int main() {
    string foo = "I am foo";
    string bar = "I am bar";

    string& fooRef = foo;  // create a reference to foo.
    fooRef += ". Hi!";  // modifies foo through the reference
    cout << fooRef << endl;
    cout << &fooRef << endl;

    // 重新赋值，地址没变，但是值变了。
    fooRef = bar;
    cout << fooRef << endl;
    cout << &fooRef << endl;

    const string& barRef = bar;  // create a const ref to bar.
    // barRef += ". Hi!";  这行是无法编译通过的。因为const references 不能改变.
}


