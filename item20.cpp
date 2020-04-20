// This items talks about weak_ptr and its uses. One interesting remark is that it is not an stand alone pointer.
// it is an extension of the share_ptr
#include <bits/stdc++.h>

#include "TestClass.hpp"

void testWeakPtr(std::weak_ptr<TestClass> &wp) {
    // To use it one needs to use the lock operation, it cannot be directly derreferenced
    auto tempSharedPtr = wp.lock();

    // if the object to which the weak pointer was deleted it will point to nullptr
    if (tempSharedPtr == nullptr) {
        std::cout << "the object was deleted " << std::endl;
    } else {
        tempSharedPtr->hello();
    }
}

int main(int argc, char *argv[]) {
    std::shared_ptr<TestClass> sptr1(new TestClass("object1"));
    std::weak_ptr<TestClass> weakPtr1(sptr1);
    testWeakPtr(weakPtr1);

    std::cout << "---------------------------Scope 1---------------------------" << std::endl;
    {
        std::weak_ptr<TestClass> weakPtr2;
        std::cout << "********************************************************" << std::endl;
        std::cout << "before scope 1.1" << std::endl;
        {
            std::shared_ptr<TestClass> sptr2(new TestClass("object2"));
            weakPtr2 = sptr2;
            testWeakPtr(weakPtr2);
        }
        std::cout << "after scope 1.1" << std::endl;
        std::cout << "********************************************************" << std::endl;
        testWeakPtr(weakPtr2);
    }
    std::cout << "---------------------------Scope 2---------------------------" << std::endl;
    {
        std::weak_ptr<TestClass> weakPtr2;
        std::shared_ptr<TestClass> sptr3;
        std::cout << "********************************************************" << std::endl;
        std::cout << "before scope 2.1" << std::endl;
        {
            std::shared_ptr<TestClass> sptr2(new TestClass("object2"));
            weakPtr2 = sptr2;
            sptr3 = weakPtr2.lock();  // the shared pointer which results from the lock function does have ownership to the object
        }
        std::cout << "after scope 2.1" << std::endl;
        std::cout << "********************************************************" << std::endl;
        testWeakPtr(weakPtr2);
    }

    return 0;
}