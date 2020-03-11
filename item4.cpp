// This items warns about the credibility of IDEs and standar function typeid to correctly state the deducted types

#include <bits/stdc++.h>

template <typename T>
void foo(const T& param) {
    std::cout << "T=" << typeid(T).name() << std::endl;
    std::cout << "param=" << typeid(param).name() << std::endl;
}

class Popo {
};

std::vector<Popo> createVector() {
    return std::vector<Popo>(5);
}

int main(int argc, char* argv[]) {
    int a_int = 5;
    const int* a_const_ptr_int;

    auto a_auto_int = a_int;
    auto a_auto_ptr_int = a_const_ptr_int;

    std::cout << typeid(a_auto_int).name() << std::endl;
    std::cout << typeid(a_auto_ptr_int).name() << std::endl;
    std::cout << typeid(foo<int>).name() << std::endl;

    const auto vpo = createVector();

    foo(&vpo[0]);  //both the T and param are printed as PK4Popo (const Popo *) which is incorrect. Correct ont is const Popo *const &param.

    return 0;
}