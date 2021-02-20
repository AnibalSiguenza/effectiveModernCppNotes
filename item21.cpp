// this item explain how make_unique and make_share are safer and more
// efficient, also explaning the cases in which this does not hold
#include <bits/stdc++.h>

#include "TestClass.hpp"

void doSomething(std::shared_ptr<TestClass> up, int anotherNumber) {}

int computeNumber() {
  std::cout << "computeNumber" << std::endl;
  return 0;
}

int main(int argc, char *argv[]) {
  // to create the smart pointers there is 2 alternatives
  std::unique_ptr<TestClass> u_ptr1(new TestClass("u1"));
  auto u_ptr2 = std::make_unique<TestClass>("u2");
  // same for shared pointer
  std::shared_ptr<TestClass> s_ptr1(new TestClass("s1"));
  auto s_ptr2 = std::make_shared<TestClass>("s2");
  /**
   * in general it is recomended to use the second option.
   * -The first reason is that with the help of auto there is no redudant
   * indication of which class we are using -The second reason it that it is
   * more efficient specially in the case of shared_ptr. Since the allocation of
   * the object and the control block is done at the same time. Whereas in the
   * first case first the object is allocated and then the control block -The
   * third is that is it safer as noted in the next example
   */

  /**
   * In this called it is not ensured the order of excecution of the calls. And
   * this situation can happen
   * 1. the new allocation is called to allocate the memory
   * 2. the compute number is ran
   * 3. the shared pointer is created pointig to the memory created by the new
   * and creating the control block
   *
   * So if the computerNumber throws an exception before the creation of the
   * shared pointer it could lead to potencial leaks.
   */
  doSomething(std::shared_ptr<TestClass>(new TestClass("funcObj")),
              computeNumber());

  /**
   *  There is reason to not used the make_shared and make_unique as:
   * 1. Custom deletes must be used
   * 2. System with memory limitation. The reason is in the example below
   */

  /**
   * Appart from the reference counter there is a weak counter which counts how
   * many weak pointers are pointing to the address. This counter is also in the
   * control block.
   */
  std::weak_ptr<TestClass> w_ptr3;
  std::weak_ptr<TestClass> w_ptr4;

  std::cout << "----------------before scope----------------" << std::endl;
  {
    std::shared_ptr<TestClass> s_ptr3(
        new TestClass("s3")); // reference count = 1, weak counter = 0
    w_ptr3 = s_ptr3;          // reference count = 1, weak counter = 1
  }
  /**
   * Here the object is destructed and dealocated. It is destructed because the
   * reference count is 0. But since the weak counter is not 0 the control block
   * is not detroid. This is need to the weak pointer will know that the object
   * has expired
   */
  std::cout << "----------------after scope-----------------" << std::endl;

  std::cout << "----------------before scope----------------" << std::endl;
  {
    auto s_ptr4 = std::make_shared<TestClass>(
        "s3");       // reference count = 1, weak counter = 0
    w_ptr4 = s_ptr4; // reference count = 1, weak counter = 1
  }                  // reference count = 0, weak counter = 1
  /**
   * Here the object is destructed BUT NOT dealocated. It is destructed because
   * the reference count is 0. But since the weak counter is not 0 the control
   * block is not deleted and since the control block and the object were
   * created together they are sharing the same memory allocation. This means
   * even though the destructor was indeed called the memory was NOT RELEASED.
   */
  std::cout << "----------------after scope-----------------" << std::endl;

  return 0;
}