// this items recommends to not overload universal reference functions. This is
// because the hierarchy of the selected function to run can be non-intuitive
// and cause conflicts specially with constructors
#include <bits/stdc++.h>

template <class T> void doNotOverload(T &&x) {
  std::cout << "Universal reference version" << std::endl;
}

void doNotOverload(int x) { std::cout << "int overload" << std::endl; }

class Foo {
private:
  std::string name;

public:
  /**
   * @brief Construct a new Foo object: this type of constructor could provide
   * some benefits if rvalue are passed as argument making use of a more
   * efficient move. But the risk is that it will overload the default copy
   * constructor
   *
   * @tparam T
   * @param name
   */
  template <typename T> Foo(T &&name) : name(std::forward<std::string>(name)){};
};

int main(int argc, char *argv[]) {
  short a = 3;

  doNotOverload("Hola");
  doNotOverload(2);
  doNotOverload(a); // one could think that this will called the integer version
                    // but since there is a exactly match for the funciton it
                    // will create the version doNotOverload(short & x)

  Foo object1("1");
  const Foo constObj("1");

  /**
   * This gives a compilation error since it is calling the universal reference
   * constructure because the default constructore has signature Foo(const & Foo
   * rhs), and this called creates a constructor template Foo(Foo & rhs) which
   * is more similar as the previos one
   */
  // Foo object2(object1);

  Foo object2(constObj); // this compiles because the object is constant so it
                         // fits perfectly on the default copy constructor
                         // thanks to the const
  return 0;
}