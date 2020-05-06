// this items defines the universal references which basically is reference which is only possible in a type deduction context and which
// takes all the characteristics (constannes and volatility) of the intance passed to it
#include <bits/stdc++.h>

#include "TestClass.hpp"

// T&& is universal because T must be type deducted and it has the double &&
template <typename T>
void universalReference(T &&x) {
}

// this is not universal because there is a const, any modification will make the function template a rvalue reference
template <typename T>
void notUniversalReference(const T &&x) {
}

int main(int argc, char *argv[]) {
    int lvalue = 0;
    const int const_lvalue = 0;
    volatile int volatile_lvalue = 0;
    const volatile int const_volatile_lvalue = 0;

    // universal reference passes the references with all its characteristics (const, volatile)
    universalReference(lvalue);                 // universalReference(int & x)
    universalReference(const_lvalue);           // universalReference(const int & x)
    universalReference(volatile_lvalue);        // universalReference(volatile int & x)
    universalReference(const_volatile_lvalue);  // universalReference(const volatile int & x)

    // samewise for rvalues
    universalReference(std::move(lvalue));                 // universalReference(int && x)
    universalReference(std::move(const_lvalue));           // universalReference(const int && x)
    universalReference(std::move(volatile_lvalue));        // universalReference(volatile int && x)
    universalReference(std::move(const_volatile_lvalue));  // universalReference(const volatile int && x)
    universalReference(3.7654);                            // universalReference(double && x)

    // auto&& is also a universal reference
    auto &&auto_lvalue = lvalue;                                             // int&
    auto &&auto_const_lvalue = const_lvalue;                                 // const int&
    auto &&auto_volatile_lvalue = volatile_lvalue;                           // volatile int&
    auto &&auto_const_volatile_lvalue = const_volatile_lvalue;               // const volatile int&
    auto &&auto_lvalue_2 = std::move(lvalue);                                // int&&
    auto &&auto_const_lvalue_2 = std::move(const_lvalue);                    // const int&&
    auto &&auto_volatile_lvalue_2 = std::move(volatile_lvalue);              // volatile int&&
    auto &&auto_const_volatile_lvalue_2 = std::move(const_volatile_lvalue);  // const volatile int&&

    //notUniversalReference(lvalue);             // error because lvalue is not an rvalue
    notUniversalReference(std::move(lvalue));  // notUniversalReference(const int && x)

    return 0;
}