// This item talks about the use of delete to avoid callers to use functions
// which should not be called. Before the common practice was to make the
// function private and deliverately not define the function. The biggest
// problem is that if a member function or friend class call it the error will
// not be noticed until link time. So delete it much better
#include <bits/stdc++.h>

class Foo {
private:
  static void
  bar() = delete; // avoid to declare deleted function as private since compiler
                  // first notice the access error and then the deleted status

public:
  Foo() = delete;
  Foo(int a){};

  // It can also be used in normal function and not just special memeber.
  void normalFunction(double a) { std::cout << a << std::endl; };
  void normalFunction(int a) = delete;

  template <typename T> void popo(T x) { std::cout << "hola!" << std::endl; }
  ~Foo(){};
};

template <>
void Foo::popo<char>(char x) =
    delete; // it can be used to delete template function cases

int main(int argc, char *argv[]) {
  // Foo f;       // Cannot be called
  // Foo::bar();  // the error states it is inaccesible, but the real intention
  // is deletion not hidding
  Foo f(1);

  // f.normalFunction(123); // error since the int case was errased
  f.normalFunction(12.3);

  // f.popo('a'); // error since the char case was errased
  f.popo(123);

  return 0;
}