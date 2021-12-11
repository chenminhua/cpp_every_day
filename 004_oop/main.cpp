#include<iostream>
#include "./ownedDog.hpp"
int main() {
    OwnedDog dog;
    dog.setName("foo");
    dog.setWeight(10);
    dog.setOwner("minhua");
    dog.print();
}
