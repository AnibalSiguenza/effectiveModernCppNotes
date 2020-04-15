// This items talks about unique pointers and how to use them
#include <bits/stdc++.h>

#include "TestClass.hpp"

class Base {
   private:
   public:
    virtual ~Base() {  // remember to put virtual or derived destructors won't be called
        std::cout << "Base destructor" << std::endl;
    };
};
class Derived1 : public Base {
   private:
   public:
    ~Derived1() {
        std::cout << "Derived1 destructor" << std::endl;
    };
};
class Derived2 : public Base {
   private:
   public:
    ~Derived2() {
        std::cout << "Derived2 destructor" << std::endl;
    };
};

/**
 * @brief Example of factory class returning a pointer to an intance from class Derived1 or Derived2
 * 
 * @param which 0 for returning Derived1, and anything else returns Derived2
 * @return auto 
 */
auto makebase(int which) {
    // one can define a special distructor as part of the unique_ptr. This is the destructor
    auto specialDestructor = [](Base *b) {
        std::cout << "Special destructor" << std::endl;
        delete b;
    };
    // this is how the unique_ptr is instaciated with the special destructor
    std::unique_ptr<Base, decltype(specialDestructor)> newObject(nullptr, specialDestructor);

    if (which == 0) {
        newObject.reset(new Derived1);
    } else {
        newObject.reset(new Derived2);
    }

    return newObject;
}

int main(int argc, char *argv[]) {
    auto bp1 = makebase(0);
    auto bp2 = makebase(1);
    // std::unique_ptr<Base> bp3 = makebase(0);  // this is incorrect since the type return includes the type of the special contructor lambda function

    std::shared_ptr<Base> sbp1 = makebase(0);  // a shareptr can receive a unique a rvalue unique pointer as argument so this is ideal for factory functions
    // std::shared_ptr<Base> sbp2 = bp2; // this is incorrect because unique pointer to assign must be an rvalue
    std::shared_ptr<Base> sbp2 = std::move(bp2);  // the move transferes the ownership of the data and invalidates bp2 using nullptr

    if (bp2 == nullptr) {
        std::cout << "The bp2 is no longer valid" << std::endl;
    }

    // One of the many advantages from unique_ptr is that the distinction bewtween an array pointer and a single element pointer is explicit
    // With the raw pointer one can do this ////////////////////////////////////
    int *oldNumPtr = new int(5);
    int *oldArrayPtr = new int[5];

    std::cout << "*oldNumPtr=" << *oldNumPtr << std::endl;
    std::cout << "**oldArrayPtr" << *oldArrayPtr << std::endl;

    for (size_t i = 0; i < 5; i++) {
        std::cout << "oldNumPtr[i]=" << oldNumPtr[i] << std::endl;  // this leads to undefined behaivor but the compiler won't complain
        std::cout << "oldArrayPtr[i]=" << oldArrayPtr[i] << std::endl;
    }
    ////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<int> numberPtr = std::make_unique<int>(123);
    std::unique_ptr<int[]> arrayPtr(new int[5]);

    std::cout << "*numberPtr=" << *numberPtr << std::endl;
    // std::cout << "*numberPtr[0]" << numberPtr[0] << std::endl; // this operator as well as -> are errased beacuse it is a vector so to acces an element a [] should be used

    for (size_t i = 0; i < 5; i++) {
        // std::cout << "numberPtr[i]=" << numberPtr[i] << std::endl; // this is an error because [] was errace since it is a single element pointer
        std::cout << "arrayPtr[i]=" << arrayPtr[i] << std::endl;
    }

    // still one should only use std::unique_ptr<T[]> with legacy code since the new STL data structures are better

    return 0;
}