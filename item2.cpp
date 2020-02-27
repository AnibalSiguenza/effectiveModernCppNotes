#include <bits/stdc++.h>

void foo(int a, int b) {
    std::cout << "a+b=" << a + b << std::endl;
}

template <typename T>
void fInvalid(T t) {
    // t(1, 2);
}

template <typename T>
void fValid(std::initializer_list<T> t) {
    // t(1, 2);
}

int main(int argc, char* argv[]) {
    // common cases:
    int a_int = 3;
    const int a_cons_tint = 3;
    const int& a_const_ref = a_int;
    int* a_ptr_int;
    const int* a_const_ptr_int;
    const int* const a_2const_ptr_int = &a_int;

    //The rules are the same as for the item 1 for the next cases /////////////////////////////////
    auto a_auto_int = a_int;                        // simply gets int
    auto a_auto_cons_tint = a_cons_tint;            // simply gets int
    auto a_auto_ref = a_int;                        // simply gets int
    auto a_auto_ptr_int = a_ptr_int;                // simply gets int *
    auto a_auto_const_ptr_int = a_const_ptr_int;    // respects the const const int *
    auto a_auto_2const_ptr_int = a_2const_ptr_int;  // second const gets ignored const int *

    auto& a_autoref_int = a_int;              // simply gets int&
    auto& a_autoref_cons_tint = a_cons_tint;  // passes the const property const int&
    auto& a_autoref_const_ref = a_const_ref;  // passes the const property const int&

    auto f_auto_value = foo;  // it uses function as a pointer ((*t)(int a, int b))
    auto& f_auto_ref = foo;   // it uses function as a ref ((&t)(int a, int b))

    // useless cases (just to impress people)
    int a_array[5] = {0};

    auto auto_array = a_array;       // it passes the argument as pointer int *t
    auto& auto_ref_array = a_array;  // it passes the argument as array! int (&)[5]

    //This is the difference between item 1 and 2 /////////////////////////////////////////////////
    auto x1 = {27};  //it gets type std::initializer_list<int>
    auto x2{27};     //it gets type int

    // fInvalid({1});   // this is invalid
    fValid({1});  // this is valid

    return 0;
}