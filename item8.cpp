// This items explains the reason to prefer nullptr instead of NULL or 0

#include <bits/stdc++.h>

// if there is only one function, it works with 0 or null
void bar(void *a) { std::cout << "bar(void*)" << std::endl; }

// if there is multiply overloading it can called the incorrect function
void foo(int a) { std::cout << "foo(int)" << std::endl; }

void foo(bool a) { std::cout << "foo(bool)" << std::endl; }

void foo(void *a) { std::cout << "foo(void*)" << std::endl; }

int main(int argc, char *argv[]) {
  bar(NULL);
  bar(0);
  bar(nullptr);

  // foo(NULL);  //gcc won't even compile
  foo(0);       // it calls the int functions
  foo(nullptr); // it calls the pointer function

  return 0;
}