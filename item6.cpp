// This item warns us about the danger of using auto with proxy classes. For
// example with bool vectors it also suggest to make every conversion explicit
#include <bits/stdc++.h>

int main(int argc, char *argv[]) {
  std::vector<bool> v = {true, true, true, true, true};

  std::cout << "v[0]=" << v[0] << std::endl;
  std::cout << "v[1]=" << v[1] << std::endl;
  std::cout << "v[2]=" << v[2] << std::endl;
  std::cout << "v[3]=" << v[3] << std::endl;
  std::cout << "v[4]=" << v[4] << std::endl;

  v[0] = false;
  std::cout << "v[0]=" << v[0] << std::endl;

  bool v1 = v[1];
  v1 = false;
  std::cout << "v[1]=" << v[1] << std::endl;

  auto v2 = v[2]; // note that v2 is type std::vector<bool>::reference
  v2 = false;
  std::cout << "v[2]=" << v[2] << std::endl;

  // Make the intentional convertions explicit
  int a = 1.321 * 3; // not clear it was the intention
  auto b = static_cast<int>(
      1.321 * 3); // here it is completely clear you wanted to cast to int

  return 0;
}