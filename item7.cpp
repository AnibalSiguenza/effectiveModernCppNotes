// This item explains the differences between thte parentesis and braquet (or uniform) initialization

#include <bits/stdc++.h>

class Foo {
   private:
    int _a;

   public:
    Foo() {}
    Foo(int a) : _a(a) {}
    ~Foo(){};
};

class Popo {
   private:
    int _num_int;
    double _num_double;

   public:
    Popo() {
        std::cout << "default" << std::endl;
    }

    Popo(const Popo& p) : _num_int(p._num_int), _num_double(p._num_double) {
        std::cout << "copy" << std::endl;
    }

    explicit Popo(int num_int, double num_double) : _num_int(num_int), _num_double(num_double) {
        std::cout << "Popo(int, double)" << std::endl;
    }

    explicit Popo(int num_int, bool num_double) : _num_int(num_int), _num_double(static_cast<double>(num_double)) {
        std::cout << "Popo(int, bool)" << std::endl;
    }

    Popo(std::initializer_list<long double> a) {
        std::cout << "initializer_list" << std::endl;
    }

    // operator double() const {
    //     return 0.123;
    // }
    // operator bool() const {
    //     return true;
    // }
    operator Foo() const {
        return Foo(0);
    }

    void print() {
        std::cout << "_num_int=" << _num_int << " _num_double=" << _num_double << std::endl;
    }
};

template <typename T, typename... Ts>
std::vector<T> createVectorParentesis(Ts... params) {
    return std::vector<T>(params...);
}

template <typename T, typename... Ts>
std::vector<T> createVectorBraquets(Ts... params) {
    return std::vector<T>{params...};
}

int main(int argc, char* argv[]) {
    //The advantage of using braquets is that it requires explicit casting when the arguments do not coincide
    Foo f1(3.432);
    // Foo f2{3.432};     //This producess error in compile time
    // Foo f3 = {3.432};  //This producess error in compile time
    Foo f4{static_cast<int>(23.5)};  //You need to explicitely cast to call the Foo(int) constructure which is less error-prone

    Popo p1(10, true);
    p1.print();

    Popo p2{10, true};  // it doesn't matter that there is a constructor with Popo(int,bool). Since it is between {} the Popo(std::initializer_list<long double>) will be called
    p2.print();

    Popo p3(10, 5.0);
    p3.print();

    Popo p4{10, 5.0};  // it doesn't matter that there is a constructor with Popo(int,double). Since it is between {} the Popo(std::initializer_list<long double>) will be called
    p4.print();

    /** The next is really tricky case. I think the best way to simply this is: if there is any chance to use the Popo(std::initializer_list<long double>)
     * the compiler will use it! Since there is a conversion for double and bool it will use the initializer_list and cast the p1 instead of 
     * using the copy constucture. Even if just one of them is defined it will run a implicit conversion and give a compile warning. Only in the 
     * case were just the Foo convertion is defined it uses the copy constructure. I think the reason is that in that case there are no constructures 
     * with a Foo class as parameter. But I ran many cases and it is quite umpredictible so I would suggest avoid to define any conversion in a class
     * with a std::initializer_list constructure.
    */
    Popo p5{p1};
    p5.print();

    Popo p6{};  // this calls the default constructure eventough it's called with bracess
    p6.print();

    /** The next is an exapmle of how the choise of using brakets or parenthesis can tranform a result which only the caller know how it should 
     * behaive
    */
    auto vPar = createVectorParentesis<int>(5, 1);
    std::cout << "vPar:" << std::endl;
    for (auto& elem : vPar) {
        std::cout << "elem=" << elem << std::endl;
    }

    auto vBra = createVectorBraquets<int>(5, 1);
    std::cout << "vBra:" << std::endl;
    for (auto& elem : vBra) {
        std::cout << "elem=" << elem << std::endl;
    }
    return 0;
}