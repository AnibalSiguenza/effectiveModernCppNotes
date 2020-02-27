#include <bits/stdc++.h>

void foo(int a, int b) {
    std::cout << "a+b=" << a + b << std::endl;
}

template <typename T>
void fvalue(T t) {
    // t(1, 2);
}

template <typename T>
void fref(T& t) {
    // t(1, 2);
}

template <typename T, std::size_t N>
constexpr std::size_t farray(T (&array)[N]) noexcept {
    for (size_t i = 0; i < N; i++) {
        std::cout << array[i] << std::endl;
    }

    return N;
}

int main(int argc, char* argv[]) {
    // common cases:
    int a_int = 3;
    const int a_cons_tint = 3;
    const int& a_const_ref = a_int;
    int* a_ptr_int;
    const int* a_const_ptr_int;
    const int* const a_2const_ptr_int = &a_int;

    fvalue(a_int);             // simply gets fvalue(int)
    fvalue(a_cons_tint);       // simply gets fvalue(int)
    fvalue(a_const_ref);       // simply gets fvalue(int)
    fvalue(a_ptr_int);         // simply gets fvalue(int *)
    fvalue(a_const_ptr_int);   // respects the const fvalue(const int *)
    fvalue(a_2const_ptr_int);  // second const gets ignored fvalue(const int *)

    fref(a_int);        // simply gets fref(int&)
    fref(a_cons_tint);  // passes the const property fref(const int&)
    fref(a_const_ref);  // passes the const property fref(const int&)

    fvalue(foo);  // it uses function as a pointer fvalue((*t)(int a, int b))
    fref(foo);    // it uses function as a ref fref((&t)(int a, int b))

    // useless cases (just to impress people)
    int a_array[5] = {0};

    fvalue(a_array);                  // it passes the argument as pointer fvalue(int *t)
    fref(a_array);                    // it passes the argument as array! fref(int (&t)[5])
    std::size_t N = farray(a_array);  // Cool example of how to use this

    return 0;
}