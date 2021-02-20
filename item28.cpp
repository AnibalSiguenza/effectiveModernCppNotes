/** This items talks about how refernce collapsing works. In short it is an and
 * operation for rvalue reference: there 2 types of reference so the function is
 * either expecting a lvalue reference or an rvalue reference, and one can parse
 * either a rvalue or an lvalue wich give us 3 possibilities lvalue -> f(&)
 * gives a lvalue reference lvalue -> f(&&) gives a lvalue reference rvalue ->
 * f(const &) gives a lvalue reference rvalue -> f(&&) gives a rvalue reference
 * So only if the reference as well as the value ar r the result will be an r
 * value ref
 */
#include <bits/stdc++.h>

template <class T> void lReferenceFunction(const T &t) {}
template <class T> void rReferenceFunction(T &&t) {}

template <typename T> class Foo {
private:
public:
  typedef T &&RvalueRef;
};

int main(int argc, char *argv[]) {
  int lvalue = 0;
  int &&rvalueref = 0;

  rReferenceFunction(lvalue); // generates rReferenceFunction<int &>(int &t)
  rReferenceFunction(123);    // generates rReferenceFunction<int>(int &&t)

  lReferenceFunction(lvalue); // generates lReferenceFunction<int>(const int &t)
  lReferenceFunction(123);    // generates lReferenceFunction<int>(const int &t)

  // same for auto
  auto &&autoLvalue = lvalue; // int &autoLvalue
  auto &&autoRvalue = 123;    // int &&autoLvalue

  // same for typedef
  using IntRvalueRef =
      Foo<int &>::RvalueRef; // typedef int &Foo<int &>::RvalueRef
  using IntRvalueRefRef =
      Foo<int &&>::RvalueRef; // typedef int &&Foo<int &&>::RvalueRef

  // tricky case: remember that rvaluereference is lvalue so this generates l
  // value call
  rReferenceFunction(rvalueref); // rReferenceFunction<int &>(int &t)
  return 0;
}