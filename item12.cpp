#include <bits/stdc++.h>

class Base {
   private:
   public:
    Base() {}

    virtual void f1() const { std::cout << "f1 Base" << std::endl; };
    virtual void f2(int x) { std::cout << "f2 Base" << std::endl; };
    virtual void f3() & { std::cout << "f3 Base" << std::endl; };
    void f4() const { std::cout << "f4 Base" << std::endl; };

    ~Base() {}
};

/**
 * @brief This class demostrates the dangers of not specifying the intention of override. All function will compile and run without 
 * any warning (I even used gcc -Wall), but they will run the base implementation.
 */
class DerivedNoOverride : public Base {
   private:
   public:
    DerivedNoOverride() {}

    virtual void f1() { std::cout << "f1 Derived NoOverride" << std::endl; };
    virtual void f2(unsigned int x) { std::cout << "f2 Derived No Override" << std::endl; };
    virtual void f3() { std::cout << "f3 Derived No Override" << std::endl; };
    void f4() const { std::cout << "f4 Derived No Override" << std::endl; };

    ~DerivedNoOverride() {}
};

/**
 * @brief This class uses the override keyword so we inmediatelly get IDE and compile errors indicating that they are no
 * overriding as we indended.
 */
// class DerivedOverride : public Base {
//    private:
//    public:
//     DerivedOverride() {}

//     virtual void f1() override { std::cout << "f1 Derived Override" << std::endl; };
//     virtual void f2(unsigned int x) override { std::cout << "f2 Derived Override" << std::endl; };
//     virtual void f3() override { std::cout << "f3 Derived Override" << std::endl; };
//     void f4() const override { std::cout << "f4 Derived Override" << std::endl; };

//     ~DerivedOverride() {}
// };

class DerivedCorrect : public Base {
   private:
   public:
    DerivedCorrect() {}

    virtual void f1() const override { std::cout << "f1 Derived Override" << std::endl; };
    virtual void f2(int x) override { std::cout << "f2 Derived Override" << std::endl; };
    virtual void f3() & override { std::cout << "f3 Derived Override" << std::endl; };
    // void f4() const override { std::cout << "f4 Derived Override" << std::endl; };  //To correct this put virtual in Base class. I did not do it for demostratrion propourses

    ~DerivedCorrect() {}
};

int main(int argc, char *argv[]) {
    Base *bp = new DerivedNoOverride();

    bp->f1();
    bp->f2(123);
    bp->f3();
    bp->f4();

    bp = new DerivedCorrect();

    bp->f1();
    bp->f2(123);
    bp->f3();

    return 0;
}