// this item speaks about the use of const iterators. Which basically mean that
// the content of the iterator remains unchanged. This can prevent mistakes and
// allow further optimizations so use when possible
#include <bits/stdc++.h>

// Examples of how to create the functions using templates
// template <typename C>
// auto cbegin(const C& container) -> decltype(std::begin(container)) {
//     return std::begin(container);
// }
// template <typename C>
// auto cend(const C& container) -> decltype(std::end(container)) {
//     return std::end(container);
// }

int main(int argc, char *argv[]) {
  int rep = 1024;
  std::vector<int> v(32768);

  // for (auto it = v.cbegin(); it != v.cend(); ++it) {
  //     // (*it)++;  // not allowed since it should be constant
  // }

  std::cout << "Non const it" << std::endl;
  auto t1 = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < rep; i++) {
    auto sum = std::accumulate(v.begin(), v.end(), 0);
  }
  auto t2 = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
  std::cout << "duration=" << duration << std::endl;

  std::cout << "const it" << std::endl;
  t1 = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < rep; i++) {
    auto sum = std::accumulate(v.cbegin(), v.cend(), 0);
  }
  t2 = std::chrono::high_resolution_clock::now();
  duration =
      std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
  std::cout << "duration=" << duration << std::endl;

  /**
   * This is an alternative using the non member function cbegin and cend. The
   * book says that this should be more generic since c++11 does not count with
   * the member function but when I ran experiments I observe the contrary. If I
   * use the flag -std=c++11 it complains about the lack of std::cbegin and
   * std::cend as non member function. And if I use c++14 it compiles just fine.
   * So I observe the contrary of what the book says.
   */
  std::cout << "const it nonmember" << std::endl;
  t1 = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < rep; i++) {
    auto sum = std::accumulate(std::cbegin(v), std::cend(v), 0);
  }
  t2 = std::chrono::high_resolution_clock::now();
  duration =
      std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
  std::cout << "duration=" << duration << std::endl;

  return 0;
}