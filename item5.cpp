// This items talks about the advantages of using auto instead of an explicit
// declaration

#include "TestClass.hpp"
#include <bits/stdc++.h>
#include <unordered_map>

int main(int argc, char *argv[]) {
  std::vector<int> v = {1, 2, 3, 4, 5};

  unsigned wrong =
      v.size(); // This can lead to mistakes in certain architectures
  std::vector<int>::size_type rightButLong =
      v.size();          // This will be always correct but it is long;
  auto right = v.size(); // This is always correct simple and short

  std::unordered_map<int, TestClass> umap;
  umap[0] = TestClass("0");
  umap[1] = TestClass("1");
  umap[2] = TestClass("2");
  umap[3] = TestClass("3");

  size_t counter = 0;
  /** The next loop will not handle any compiler warning and it appears to be
   * equivalent to the best implementation. But since the key of a unorderer map
   * is set to constant the pairs save in this data structure have the next
   * signature std::pair<const int, TestClass>. Therefore the compiler creates a
   * temporary instance and performs a copy making an "implicit casting". This
   * causes an extra copy constructure and  distroctor call peer iteration. Also
   * the addres of elem will be different as the addresses of the pairs in the
   * umap.
   */
  std::cout << "---------Starting incorrect loop--------------" << std::endl;
  for (const std::pair<int, TestClass> &elem : umap) {
    std::cout << "Loop number " << counter << ":" << std::endl;
    counter++;
  }
  std::cout << "---------End of incorrect loop----------------" << std::endl;

  counter = 0;
  /** This is how it would correctly work but it is long to write
   */
  std::cout << "-----------Starting correct loop--------------" << std::endl;
  for (const std::pair<const int, TestClass> &elem : umap) {
    std::cout << "Loop number " << counter << ":" << std::endl;
    counter++;
  }
  std::cout << "-----------End of correct loop----------------" << std::endl;

  counter = 0;
  /** So  this is the best and simplest option
   */
  std::cout << "-----------Starting correct loop--------------" << std::endl;
  for (auto &elem : umap) {
    std::cout << "Loop number " << counter << ":" << std::endl;
    counter++;
  }
  std::cout << "-----------End of correct loop----------------" << std::endl;

  return 0;
}