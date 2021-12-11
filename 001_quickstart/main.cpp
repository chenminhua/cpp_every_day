#include<iostream>

// string %s, int %d
void print(char const* myString) {
    printf("String %s\n", myString);
}

int main() {
    std::cout << "hello world" << std::endl;

    // sizeof
    std::cout << "sizeof(char) = " << sizeof(char) << std::endl;
    int* a;
    std::cout << "sizeof(ptr) = " << sizeof(a) << std::endl;


}
