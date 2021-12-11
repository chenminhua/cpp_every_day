#include "./dog.hpp"
class OwnedDog : public Dog {

public:
    void setOwner(const std::string& dogsOwner);

    void print() const override;

private:
    std::string owner;
};
