// this item talks about the new scoped enums which should be prefered from the
// previous existend unscope enums
#include <bits/stdc++.h>

enum Color { white, black, yellow };
// auto white = true;  // Error because white is already declared

enum class Direction { north, south, east, west };

auto east = true; // Now this is possible since the enums are in the namespace
                  // of Direction

void foo(size_t x) {
  std::cout << "Foo: "
            << "x=" << x << std::endl;
}

/** One can also do fordward declaration this helps to avoid the compiler to
 * recompile all the system since it can be in a header that is included in all
 * part of the system. So a change on it would require a hole new compilation.
 */
enum class Names : std::uint8_t;

void bar(Names n) { std::cout << "n=" << static_cast<size_t>(n) << std::endl; }

enum class Names : std::uint8_t { Anibal, Juan, Pepe };

/** Something which is often needed is a cast to the underlying type since one
 * cannot compare or permore many task unless it is explicity casted. This
 * function can serve as a general casting.
 */

template <typename E> constexpr auto toUType(E enumerator) noexcept {
  return static_cast<std::underlying_type_t<E>>(enumerator);
}

int main(int argc, char *argv[]) {
  std::cout << "White=" << white << std::endl;
  std::cout << "Black=" << black << std::endl;
  std::cout << "Yellow=" << yellow << std::endl;

  foo(white);
  // foo(Direction::north);  // Error since the convertion must be explicit
  foo(static_cast<size_t>(Direction::north));

  if (white > 1.3) {
  }
  // if (Direction::north > 1.3) {  // Error since the convertion must be
  // explicit
  // }
  if (static_cast<double>(Direction::north) > 1.3) {
  }

  bar(Names::Anibal);

  // Showing general casting function
  auto north = toUType(Direction::north);
  auto Anibal = toUType(Names::Anibal);

  return 0;
}