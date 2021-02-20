// This items talks about the advantages and disadvantages of declaring a
// function noexcept
#include "item14.hpp"

#include <bits/stdc++.h>

#include "TestClass.hpp"
#include "TestClassNoExcept.hpp"

/**
 * noexcept is part of the signature of the function which means that if the
 * function is declared without it it will made a linker error. This means that
 * if one commits to make a function noexcept is a long term commitment
 * otherwise it can break clien side code0
 */
// void foo();  // this make a duplication error
void foo() noexcept;

template <typename T> T moveIfNoExcept(T t) { return std::move_if_noexcept(t); }

int main(int argc, char *argv[]) {
  foo();
  std::vector<TestClass> v;
  std::vector<TestClassNoExcept> vne;

  /**
   * This is a prove how the STL further uptimizes if the user class has
   * noexcept in the move constructures
   */
  auto t1 = std::chrono::high_resolution_clock::now();
  std::cout << "Without noexcept" << std::endl;
  for (size_t i = 0; i < 8; i++) {
    v.push_back(TestClass(std::to_string(
        i + 1))); // here it will performe copies every time the vector resizes
  }
  auto t2 = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
  std::cout << "duration=" << duration << std::endl;

  std::cout << std::endl;

  t1 = std::chrono::high_resolution_clock::now();
  std::cout << "With noexcept" << std::endl;
  for (size_t i = 0; i < 8; i++) {
    vne.push_back(TestClassNoExcept(std::to_string(
        i + 1))); // here it will performe moves every time the vector resizes
                  // making this code more efficient
  }
  t2 = std::chrono::high_resolution_clock::now();
  duration =
      std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
  std::cout << "duration=" << duration << std::endl;

  // The reson why this is more efficient is the STL uses the
  // std::move_if_noexcept
  std::cout << std::endl << "Move if no except demostration" << std::endl;
  auto temp1 = moveIfNoExcept(TestClass("A"));
  auto temp2 = moveIfNoExcept(TestClassNoExcept("B"));

  return 0;
}