#include<iostream>

class Dog {
    std::string name;
    int weight;

public:
    // default constructor
    Dog();

    void setName(const std::string& dogsName);
    void setWeight(int dogsWeight);

    // 虚函数来了，to be overridden
    // 不改变对象状态的方法应该被标记为 const。
    virtual void print() const;

    void bark() const {std::cout << name << "barks!\n";}

    // the destructor should be virtual if a class is to be derived from;
    // if it's not virtual, then the derived class's destructor will not be called if the object is destroyed through a base-class refreence or pointer.
    virtual ~Dog();
};
