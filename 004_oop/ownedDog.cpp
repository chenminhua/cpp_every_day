#include "./ownedDog.hpp"
void OwnedDog::setOwner(const std::string& dogsOwner) {
    owner = dogsOwner;
}

void OwnedDog::print() const {
    Dog::print();
    std::cout << "Dog is owned by " << owner << std::endl;
}
