// this items talks about the possibility to move capture a rvalue in a lamda
// function
#include <bits/stdc++.h>

#include "TestClass.hpp"

int main(int argc, char *argv[]) {
  /**
   * @brief this is how to capture using move semantics. This syntax is only
   * posible grom c++14 on. To see how to do it in c++11 consult the book
   *
   * Note: the element will be constant by default so only const function will
   * be able to be called.
   *
   */
  auto f1 = [tc = std::move(TestClass("test class obj 1"))]() {
    // tc.setName("New name"); // does not compile because it is not a const
    // function
    tc.hello();
  };
  f1();

  auto f2 = [tc = std::move(TestClass("test class obj 2"))]() mutable {
    tc.setName("New name");
    tc.hello();
  };
  f2();

  // the move capture is specialy impotant with copy disabled and move enabled
  // classes as unique pointer because it cannot be captured by value unless it
  // is move captured
  auto tc_ptr = std::make_unique<TestClass>("Pointer object");

  // auto f3 = [tc_ptr]() {}; //does not compile because it is copy disabled
  auto f3 = [tc_ptr = std::move(tc_ptr)]() { tc_ptr->hello(); };
  f3();

  return 0;
}