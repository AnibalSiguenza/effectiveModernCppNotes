// This item recoments to repfer alias over typedefs

#include <bits/stdc++.h>

#include <memory>

// Equivalent functionality between typedef and aliases:
// typedef std::unordered_map<int, std::string> MapIS;
// typedef std::unique_ptr<MapIS> UPtrMapIS;
using MapIS = std::unordered_map<int, std::string>;
using UPtrMapIS = std::unique_ptr<MapIS>;

// But also alias can be used to create alias temples which is not possible with
// typedef
template <typename T> using HashVector = std::unordered_map<T, std::vector<T>>;

// It can also help to simplify class templates
template <typename T> using vectorType = std::vector<T>;

// previos syntax to do it
template <typename T> struct vectorTypeStruct { typedef std::vector<T> type; };

template <typename T> struct Foo {
  vectorType<T> v1; // cleaner syntax to declare member of type vectorType<T>
  typename vectorTypeStruct<T>::type
      v2; // with the previos syntax one needed to specify that
          // vectorTypeStruct<T>::type is a type
};

int main(int argc, char *argv[]) {
  // To avoid the artritis of writing expresions like this
  std::unique_ptr<std::unordered_map<int, std::string>> um_ptr_artritis =
      std::make_unique<std::unordered_map<int, std::string>>(
          std::unordered_map<int,
                             std::string>()); // to be fair I could have use an
                                              // auto, but this proves a point

  // alias or typedef can help to make it shorter and cleaner
  UPtrMapIS um_ptr = std::make_unique<MapIS>(MapIS());

  // std::unique_ptr<int> ptr = std::make_unique<int>(new int(23));
  (*um_ptr)[0] = "hola";
  std::cout << (*um_ptr)[0] << std::endl;

  HashVector<int> hv;
  hv[0] = {1, 23, 4, 5};
  for (auto &elem : hv[0]) {
    std::cout << elem << std::endl;
  }

  Foo<int> f;
  f.v1 = {1, 2, 3, 4, 5};
  f.v2.push_back(2);
  f.v2.push_back(3);
  f.v2.push_back(4);
  f.v2.push_back(5);

  for (auto &elem : f.v1) {
    std::cout << elem << std::endl;
  }

  return 0;
}