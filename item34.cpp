// this item explains how using lamda function is better than using std::bind.
// Specially after c++14 there is practically no good reason to use bind
// according to Meyers
#include <bits/stdc++.h>

using namespace std::placeholders; // necesary to use the placeholders _1 in
                                   // blind

void foo(int a, int b) { std::cout << "a+b=" << a + b << std::endl; }

int main(int argc, char *argv[]) {
  auto fooL = [](auto a) {
    foo(a, 10); // here we set the sencond argument with the desired value and
                // the intension is clear
  };
  fooL(2);

  auto fooB = std::bind(foo, _1, 10);
  fooB(2);

  return 0;
}