#include<iostream>

namespace First {
    namespace Nested {
        void foo() {
            printf("This is First::Nested::Foo\n");
        }
    }
}

namespace Second {
    void foo() {
        printf("this is Second::foo\n");
    }
}

void foo() {
    printf("this is global foo\n");
}

int main() {
    Second::foo();
    First::Nested::foo();
    foo();
    ::foo();
}
