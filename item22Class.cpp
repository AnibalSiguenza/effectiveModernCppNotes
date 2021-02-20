#include "item22Class.hpp"

// this are the dependencies hidded from the other units
#include <iostream>

#include "TestClassNoExcept.hpp"

// Now we implement the incomplete type
struct Popo::Impl {
  std::string str;
  TestClassNoExcept tc;
};

Popo::Popo() : impl(std::make_unique<Impl>()) {}

// With default we indicate that the default move semantics for the string and
// TestClassNoExcept fit our necessities
Popo::Popo(Popo &&rhs) noexcept = default;
Popo &Popo::operator=(Popo &&rhs) noexcept = default;

// We have to define a custom copy to create a real copy and not a hollow one
Popo::Popo(const Popo &rhs) noexcept : impl(nullptr) {
  if (rhs.impl) {
    impl = std::make_unique<Impl>(*rhs.impl);
  }
}
Popo &Popo::operator=(const Popo &rhs) noexcept {
  if (!rhs.impl) {
    impl.reset();
  } else if (!impl) {
    impl = std::make_unique<Impl>(*rhs.impl);
  } else {
    *impl = *rhs.impl;
  }

  return *this;
}

void Popo::hello() { impl->tc.hello(); }

Popo::~Popo() = default;