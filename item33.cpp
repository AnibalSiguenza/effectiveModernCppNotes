// this items explain how to use perfect forward for lamda function. This
// available from c++14 on
#include <bits/stdc++.h>

#include "TestClass.hpp"

void foo(TestClass &tc) {
  tc.hello();
  std::cout << "lreference foo" << std::endl;
}
void foo(const TestClass &tc) {
  tc.hello();
  std::cout << "const lreference foo" << std::endl;
}
void foo(TestClass &&tc) {
  tc.hello();
  std::cout << "rreference foo" << std::endl;
}

void foo(TestClass &&tc, int i) {
  std::cout << "2 argument rvalue foo" << std::endl;
}

int main(int argc, char *argv[]) {
  TestClass tc("lvalue");
  const TestClass const_tc("const lvalue");
  auto lamda1 = [](auto &&tc) { // using auto && is equivalent to use T &&
    foo(std::forward<decltype(tc)>(tc));
  };

  lamda1(tc);
  lamda1(const_tc);
  lamda1(std::move(TestClass("rvalue1")));

  auto lamda2 =
      [](auto &&...t) { // using auto && ... is equivalent to use T && ... args
        foo(std::forward<decltype(t)>(t)...);
      };

  lamda2(tc);
  lamda2(const_tc);
  lamda2(std::move(TestClass("rvalue2")));
  lamda2(std::move(TestClass("rvalue3")), 123);

  return 0;
}