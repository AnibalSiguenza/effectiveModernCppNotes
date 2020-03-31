// This item explains the use of constexpr which marks functions and variables which are constant and known on compile time
#include <bits/stdc++.h>

constexpr int foo(int a) {
    return a * a;
}

constexpr int foo(int a);
// int foo(int a); //this is not allows because constexpr is part of the interface, so it would take it as a duplicate. This means
// if one commits to have a constexpr function it needs to remain as such or it can break client side code.

class NoLiteral {
   public:
    NoLiteral() {}
};
class Literal {
   public:
    constexpr Literal() {}
};

/////////////////////////////////////////////////////////////////////////
class Point {
   private:
    int _x, _y;

   public:
    constexpr Point() : _x(0), _y(0) {}
    constexpr Point(int x, int y) : _x(x), _y(y) {}

    constexpr int getX() const noexcept { return _x; }
    constexpr int getY() const noexcept { return _y; }

    constexpr void setX(int x) { _x = x; }  // without constexpr here this function cannot be called on reflection
    constexpr void setY(int y) { _y = y; }  // without constexpr here this function cannot be called on reflection
};

constexpr Point vectorSum(Point a, Point b) {
    return Point(a.getX() + b.getX(), a.getY() + b.getY());
}
constexpr Point reflection(Point a) {
    Point r;
    r.setX(-a.getX());  // this can be used only from c++14 on
    r.setY(-a.getY());  // this can be used only from c++14 on
    return r;
}
/////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    // Using function for obtaining consexpr values /////////////////////////////////////////////////////////////////////
    constexpr auto ceint = foo(3);        // to have a constexpr value one must mark it as such it is not suficient that the function is declared as constexpr
    [[maybe_unused]] auto nint = foo(4);  // this is a run-time variable since it was not marked with the keyword constexpr

    [[maybe_unused]] std::array<int, ceint> array;
    // std::array<int, nint> array;  // Error since nint is not constexpr
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // constexpr NoLiteral nl;  // this is not allowed since the class NoLiteral is not literal which means it cannot be intanciated at compile time
    constexpr Literal l;  // this is a literal since we add the constexpr to the default constructure now it can be intanciated at compile time

    constexpr Point p1(1, 3);
    constexpr Point p2(2, 4);
    constexpr auto p1x = p1.getX();
    [[maybe_unused]] std::array<int, p1x> array2;

    constexpr auto p3 = vectorSum(p1, p2);
    std::cout << "p3.getX()=" << p3.getX() << std::endl;
    std::cout << "p3.getY()=" << p3.getY() << std::endl;

    constexpr auto rp3 = reflection(p3);
    std::cout << "rp3.getX()=" << rp3.getX() << std::endl;
    std::cout << "rp3.getY()=" << rp3.getY() << std::endl;

    // This can also be called in a noncontexpr context
    Point nonconst;
    nonconst.setX(3);

    return 0;
}