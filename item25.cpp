// this items talks about when to use move and when to use forward. In short, if the object was received as an rvalue use move,
// if the object was received as a universal reference use forward
#include <bits/stdc++.h>

#include "TestClass.hpp"

void foo(TestClass tc) {
    tc.hello();
}

void fmove(TestClass &&tc) {
    foo(tc);
    foo(std::move(tc));  // use move because it used a rvalue reference.
    // before this is how to use an rvalue. It needs to be further pass with move, but only the last time it is used.
    // After it was moved it will be invalid
    foo(std::move(tc));  // calling foo with an invalid rvalue
}

template <class T>
void fforward(T &&t) {
    foo(t);
    foo(std::forward<T>(t));  // use forward since it used a universal reference.
    // the same precaution must be taken into account with universal reference because it can be called with an rvalue
    // in that case the next calls would be invalid
    foo(std::forward<T>(t));  // invalid call for the rvalue reference case
}

/**
 * @brief This function is a naive trap. One could think that is avoiding an unercesary copy contructor for a temporal
 * object, and it will use the more efficient move contructor, but most compiler will perform a return value optimization 
 * and never call the copy constructor. By making the move a temporal object is created and then moved.
 * 
 * @return TestClass 
 */
TestClass incorrectFunction() {
    TestClass tc("Temporal incorrectFunction");
    return std::move(tc);
}

/**
 * @brief This is the correct aproach simply leaving the return value since most compiler will do a return value optimization
 * and only called the constructor without any copy
 * 
 * @return TestClass 
 */
TestClass correctFunction() {
    TestClass tc("Temporal correctFunction");
    return tc;
}

int main(int argc, char *argv[]) {
    TestClass lvalue1("lvalue1");

    fmove(std::move(lvalue1));
    fmove(TestClass("rvalue1"));

    std::cout << "----------------------------" << std::endl;
    TestClass lvalue2("lvalue2");
    fforward(lvalue2);
    fforward(TestClass("rvalue2"));

    std::cout << "------------- RVO test -------------" << std::endl;
    auto tc1 = incorrectFunction();
    auto tc2 = correctFunction();

    std::cout << "-------before main return----------" << std::endl;
    return 0;
}