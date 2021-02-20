
// This item explains the decltype function which returns the type of the
// variable passed as argument

#include <bits/stdc++.h>

template <typename T> class Popo {};

// Usefull examples:
// This does not return access to the container because the returned variable
// loses the reference properties
template <typename Container, typename Index>
auto wrongAutchAndAccess(Container &c, Index i) {
  return c[i];
}
// This conserves the reference properties
template <typename Container, typename Index>
auto autchAndAccess1(Container &c, Index i) -> decltype(c[i]) {
  return c[i];
}
// This is c++14 and conserves the reference properties
template <typename Container, typename Index>
decltype(auto) autchAndAccess2(Container &c, Index i) {
  return c[i];
}
// This is c++14 fanciest version using perfect forwarding
template <typename Container, typename Index>
decltype(auto) autchAndAccess3(Container &&c, Index i) {
  return std::forward<Container>(c)[i];
}

// Strange cases
decltype(auto) foo() {
  int a = 3;
  // return a;  //this would be normal int foo()
  return (a); // this returns a reference to a local variale which can lead to
              // mistakes
}

int main(int argc, char *argv[]) {
  // common cases:
  int a_int = 3;
  int &a_ref = a_int;
  const int a_cons_tint = 3;
  const int &a_const_ref = a_int;
  int *a_ptr_int;
  const int *a_const_ptr_int;
  const int *const a_2const_ptr_int = &a_int;

  decltype(auto) auto_int = a_int;
  decltype(auto) auto_ref = a_ref;
  decltype(auto) auto_cons_tint = a_cons_tint;
  decltype(auto) auto_const_ref = a_const_ref;
  decltype(auto) auto_ptr_int = a_ptr_int;
  decltype(auto) auto_const_ptr_int = a_const_ptr_int;
  decltype(auto) auto_2const_ptr_int = a_2const_ptr_int;

  // All this cases return exactly what is expected which is the exact match of
  // types
  Popo<decltype(a_int)> p_int;                       // Popo<int>
  Popo<decltype(a_ref)> p_ref;                       // Popo<int &>
  Popo<decltype(a_cons_tint)> p_cons_tint;           // Popo<const int>
  Popo<decltype(a_const_ref)> p_const_ref;           // Popo<const int&>
  Popo<decltype(a_ptr_int)> p_ptr_int;               // Popo<int*>
  Popo<decltype(a_const_ptr_int)> p_const_ptr_int;   // Popo<const int*>
  Popo<decltype(a_2const_ptr_int)> p_2const_ptr_int; // Popo<const int* const>

  // Usefull examples
  // function to access an element from an arbitrary container
  std::vector<int> v1 = {1, 2, 3, 4};

  // int& wrongElem = wrongAutchAndAccess(v1, 2); //compilation error because
  // the return type is only int wrongElem = 13;
  std::cout << "v1[2]=" << v1[2] << std::endl;

  int &elem1 = autchAndAccess1(v1, 2);
  elem1 = 23;
  std::cout << "v1[2]=" << v1[2] << std::endl;

  int &elem2 = autchAndAccess2(v1, 2);
  elem2 = 54;
  std::cout << "v1[2]=" << v1[2] << std::endl;

  int &elem3 = autchAndAccess3(v1, 2);
  elem3 = 33;
  std::cout << "v1[2]=" << v1[2] << std::endl;

  // Strange cases
  int &num = foo();
  std::cout << num << std::endl;

  return 0;
}