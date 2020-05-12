// this items talks about the cases were the perfect forward does not work.
#include <bits/stdc++.h>

// Basically the function which will be conciderer fail are the ones which are not able to run f(std::forward<T>(t)) as if we simply send f(t)

void vecFunction(const std::vector<int> &v) {
    for (auto &elem : v) {
        std::cout << elem << std::endl;
    }
}

template <class T>
void fwf1(T &&t) {
    vecFunction(std::forward<T>(t));
}

void ptrFunction(const int *ptr) {
    if (ptr != nullptr) {
        std::cout << *ptr << std::endl;
    } else {
        std::cout << "nullptr" << std::endl;
    }
}

template <class T>
void fwf2(T &&t) {
    ptrFunction(std::forward<T>(t));
}

int main(int argc, char *argv[]) {
    vecFunction({1, 2, 3, 4});
    // fwf1({1, 2, 3, 4});  // not posible
    auto v = {1, 2, 3, 4};
    fwf1(v);  // work arround

    ptrFunction(0);
    ptrFunction(NULL);
    ptrFunction(nullptr);
    // fwf2(0);     // doesn't work because the type ist int
    // fwf2(NULL);  // doesn't work because the type is long
    fwf2(nullptr);  // work and this is what you should be doing any way! if you don't believe me return to item 8

    // there were more cases check the book

    return 0;
}