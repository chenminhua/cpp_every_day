#include "./dog.hpp"

Dog::Dog() {
    std::cout << "a dog has been constructed" << std::endl;
}

void Dog::setName(const std::string& dogsName) {
    name = dogsName;
}

void Dog::setWeight(int dogsWeight) {
    weight = dogsWeight;
}

void Dog::print() const {
    std::cout << "Dog is " << name << " and weights " << weight << std::endl;
}

Dog::~Dog() {
    std::cout << "goodbye " << name << "\n";
}
