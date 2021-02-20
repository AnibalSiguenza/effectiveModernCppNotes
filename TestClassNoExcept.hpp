#include <bits/stdc++.h>

class TestClassNoExcept {
  std::string _name;

public:
  TestClassNoExcept() {
    _name = std::string("Default");
    std::cout << "Creating " << _name << std::endl;
  }
  TestClassNoExcept(std::string name) : _name(name) {
    std::cout << "Creating " << _name << std::endl;
  }
  virtual ~TestClassNoExcept() {
    std::cout << "Destroying " << _name << std::endl;
  }
  TestClassNoExcept(const TestClassNoExcept &x) {
    _name = x._name;
    std::cout << "Copy constructing " << _name << std::endl;
  }
  const TestClassNoExcept &operator=(const TestClassNoExcept &x) {
    _name = x._name;
    std::cout << "Assign " << _name << std::endl;
    return *this;
  }
  const TestClassNoExcept &operator=(const TestClassNoExcept &&x) noexcept {
    _name = x._name;
    std::cout << "Move Assign " << _name << std::endl;
    return *this;
  }
  TestClassNoExcept(const TestClassNoExcept &&x) noexcept {
    _name = x._name;
    std::cout << "Move Constructor " << _name << std::endl;
  }
  void hello() { std::cout << _name << " says hi! ;)" << std::endl; }
};