// this item talks about the solution for the problem presented in item26 which is the inability to averload a universal reference function
#include <bits/stdc++.h>

// one alternative is to use tag dispath /////////////////////////////////////
template <class T>
void uniRefFuncImpl(T &&x, std::false_type) {
    std::cout << "everything else implementation" << std::endl;
}
template <class T>
void uniRefFuncImpl(T &&x, std::true_type) {
    std::cout << "int implementation" << std::endl;
}

template <class T>
void uniRefFunc(T &&x) {
    uniRefFuncImpl(std::forward<T>(x), std::is_integral<std::remove_reference_t<T>>());
}
/////////////////////////////////////////////////////////////////////////////

// for class costructures this one can constrain the templates ignore the template for element of the class and subclasses ///
class Foo {
   private:
    std::string name;

   public:
    // note: this is one of the ugliest codes your eyes will see hahaha
    template <typename T,
              typename = std::enable_if_t<
                  !std::is_base_of<Foo, std::decay_t<T>>::value &&
                  !std::is_integral<std::remove_reference_t<T>>()>>
    explicit Foo(T &&name) : name(std::forward<T>(name)) {
        std::cout << "universal reference constructor" << std::endl;
    };

    explicit Foo(int) {
        std::cout << "int constructor" << std::endl;
    };
};

int main(int argc, char *argv[]) {
    uniRefFunc("asd");
    uniRefFunc(2.3123);
    uniRefFunc(2);

    Foo obj1("Hola");
    Foo obj2(13);
    auto obj3(obj1);  // now the copy works without trouble since it is not replacing any copy constructor

    return 0;
}