#include <bits/stdc++.h>

class TestClass {
    std::string _name;

   public:
    TestClass() {
        _name = std::string("Default");
        std::cout << "Creating " << _name << std::endl;
    }
    TestClass(std::string name) : _name(name) {
        std::cout << "Creating " << _name << std::endl;
    }
    virtual ~TestClass() {
        std::cout << "Destroying " << _name << std::endl;
    }
    TestClass(const TestClass& x) {
        _name = x._name;
        std::cout << "Copy constructing " << _name << std::endl;
    }
    const TestClass& operator=(const TestClass& x) {
        _name = x._name;
        std::cout << "Assign " << _name << std::endl;
        return *this;
    }
    const TestClass& operator=(const TestClass&& x) {
        _name = x._name;
        std::cout << "Move Assign " << _name << std::endl;
        return *this;
    }
    TestClass(const TestClass&& x) {
        _name = x._name;
        std::cout << "Move Constructor " << _name << std::endl;
    }
    void hello() {
        std::cout << _name << " says hi! ;)" << std::endl;
    }
};