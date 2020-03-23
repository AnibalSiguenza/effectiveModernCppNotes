// In item 12 is also discused the concept of reference qualifier, but since it's quite independent I decided to explain it in this file
#include <bits/stdc++.h>

#include "TestClass.hpp"

class Foo {
   private:
    TestClass tc;

   public:
    Foo(std::string name) : tc(name){};

    TestClass& getData() { return tc; }

    ~Foo(){};
};

class Bar {
   private:
    TestClass tc;

   public:
    Bar(std::string name) : tc(name){};

    // the reference qualifier & at the end indicates that this will apply for lvalues of (*this)
    TestClass& getData() & { return tc; }
    // the reference qualifier && at the end indicates that this will apply for rvalues of (*this)
    TestClass&& getData() && { return std::move(tc); }

    ~Bar(){};
};

int main(int argc, char* argv[]) {
    Foo f("fInstance");
    Bar b("bInstance");

    // The next 2 lines both call the copy constructor even though one is receiving the data from an lvalue and the other one from an rvalue
    auto rec1 = f.getData();               // rec1 receives data from an lvalue, and calls copy constructure
    auto rec2 = Foo("fRValue").getData();  // rec2 receies data from an rvalue, and calls COPY constructure

    // Here they will behave different depending if (*this) is rvalue or lvalue.
    auto rec3 = b.getData();               // rec1 receives data from an lvalue, and calls copy constructure
    auto rec4 = Bar("bRValue").getData();  // rec2 receies data from an rvalue, and calls MOVE constructure

    return 0;
}