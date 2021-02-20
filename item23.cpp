// this item talks about the difference and real implementation of move and
// fordward. The first makes a cast to rvalue always, the second is a
// conditional casting which makes is only if the variable was initialize with
// an rvalue.
#include <bits/stdc++.h>

void foo(int &tc) { std::cout << "lvalue foo" << std::endl; }
void foo(int &&tc) { std::cout << "rvalue foo" << std::endl; }

template <class T> void fmove(T &&t) { foo(std::move(t)); }

template <class T> void fforward(T &&t) { foo(std::forward<T>(t)); }

int main(int argc, char *argv[]) {
  int lvalue = 0;

  // move always cast the value to an rvalue so the next 2 functions will called
  // the rvalue version of foo
  fmove(0);      // calls the foo(int &&tc)
  fmove(lvalue); // calls the foo(int &&tc)

  // forward cast the value to rvalue only if the value was a rvalue since this
  // is universal reference the lvalue calls a fforward(int & t). And passes
  // forwards the reference as it was received to the foo function
  fforward(0);      // calls the foo(int &&tc)
  fforward(lvalue); // calls the foo(int &tc)

  return 0;
}