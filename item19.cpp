// This items talks about the share pointer which is a pointer with shared
// ownership
#include <bits/stdc++.h>

#include "TestClass.hpp"

int main(int argc, char *argv[]) {
  std::cout << "---------------------------Scope 1---------------------------"
            << std::endl;
  {
    std::shared_ptr<TestClass> outsideSharedPtr;

    std::cout << "********************************************************"
              << std::endl;
    std::cout << "before scope 1.1" << std::endl;
    {
      std::shared_ptr<TestClass> temporalSharedPtr(
          new TestClass("object1")); // reference count of object1=1
      // object1 is deleted right here at the end of scope 1.1 because it is
      // only owned by temporalSharedPtr
    } // reference count of object1=0
    std::cout << "after scope 1.1" << std::endl;
    std::cout << "********************************************************"
              << std::endl;

    std::cout << "before scope 1.2" << std::endl;
    {
      std::shared_ptr<TestClass> temporalSharedPtr(
          new TestClass("object2"));        // reference count of object2=1
      outsideSharedPtr = temporalSharedPtr; // reference count of object2=2
    }                                       // reference count of object2=1
    std::cout << "after scope 1.2" << std::endl;
    std::cout << "********************************************************"
              << std::endl;
    // object2 is deleted here and not at the end of scope 1.2 because
    // outsideSharedPtr also shares the ownership and it is deleted here
  } // reference count of object2=0
  std::cout << "-------------------------------------------------------------"
            << std::endl;

  std::cout << "---------------------------Scope 2---------------------------"
            << std::endl;
  {
    std::shared_ptr<TestClass> outsideSharedPtr;

    std::cout << "********************************************************"
              << std::endl;
    std::cout << "before scope 2.1" << std::endl;
    {
      std::shared_ptr<TestClass> temporalSharedPtr(
          new TestClass("object1"));        // reference count of object1=1
      outsideSharedPtr = temporalSharedPtr; // reference count of object1=2
    }                                       // reference count of object1=1
    std::cout << "after scope 2.1" << std::endl;
    std::cout << "********************************************************"
              << std::endl;

    std::cout << "before scope 2.2" << std::endl;
    {
      std::shared_ptr<TestClass> temporalSharedPtr(
          new TestClass("object2")); // reference count of object2=1
      // the object1 is deleted here since the assigned operation of the next
      // line decreases the reference count on object1, since outsideSharedPtr
      // will not longer be pointing to it
      outsideSharedPtr = temporalSharedPtr; // reference count of object2=2 AND
                                            // reference count of object1=0
    }                                       // reference count of object2=1
    std::cout << "after scope 2.2" << std::endl;
    std::cout << "********************************************************"
              << std::endl;
    // object2 is deleted here and not at the end of scope 2.2 because
    // outsideSharedPtr also shares the ownership and it is deleted here
  } // reference count of object2=0

  std::cout << "---------------------------Scope 3---------------------------"
            << std::endl;
  {
    std::shared_ptr<TestClass> outsideSharedPtr(
        new TestClass("object1")); // reference count of object1=1

    std::cout << "********************************************************"
              << std::endl;
    std::cout << "before scope 3.1" << std::endl;
    {
      std::shared_ptr<TestClass> temporalSharedPtr =
          outsideSharedPtr; // reference count of object1=2
    }                       // reference count of object1=1
    std::cout << "after scope 3.1" << std::endl;
    std::cout << "********************************************************"
              << std::endl;

    std::cout << "********************************************************"
              << std::endl;
    std::cout << "before scope 3.2" << std::endl;
    {
      std::shared_ptr<TestClass> temporalSharedPtr =
          std::move(outsideSharedPtr); // reference count of object1=1
      // object1 is deleted here since the count was not increased beacuse it
      // was moved and not copied
    } // reference count of object1=0
    std::cout << "after scope 3.2" << std::endl;
    std::cout << "********************************************************"
              << std::endl;
  }
  std::cout << "-------------------------------------------------------------"
            << std::endl;

  /**
   * Shared pointers can also have custom destructors defined, but they are more
   * flexible as the unique_ptr syntax since they are not part of the signature
   * type. Therefore they can be saved in the same vector for example. This is
   * achieved by adding a pinter to the custom destructor in the control block
   * which is created for the shared pointers
   */
  auto customDestructor1 = [](TestClass *tc) {
    std::cout << "custom Destructor 1" << std::endl;
    delete tc;
  };
  auto customDestructor2 = [](TestClass *tc) {
    std::cout << "custom Destructor 1" << std::endl;
    delete tc;
  };

  std::shared_ptr<TestClass> tcsp1(new TestClass("Object1"), customDestructor1);
  std::shared_ptr<TestClass> tcsp2(new TestClass("Object2"), customDestructor2);
  std::vector<std::shared_ptr<TestClass>> v{tcsp1, tcsp2};

  return 0;
}