// this items advices never to use default captures by value nor by reference in
// lamda function. this could lead to hanging references in both cases
#include <bits/stdc++.h>

void addFunction(std::vector<std::function<bool(int)>> &funcVector) {
  static int divisor = 5; // this is a static value

  /**
   * @brief One could think that the divisor inside the lamda function is "been
   * captured", but in reality lamda functions DOES NOT CAPTURE STATIC VALUES.
   * Try to explicit declare a capture uncomenting next line. So the default
   * capture simply ignores the capture of divisor and  DIRECTLY uses the
   * divisor static variable. SUUUUPER dangerous
   */
  // funcVector.emplace_back([divisor](int x) { return true; });  // wont
  // compile because divisor is static and cannot be captured
  funcVector.emplace_back([=](int x) {
    std::cout << "divisor=" << divisor << std::endl;
    return 0 == (x % divisor);
  });
  auto res = funcVector[2](6);
  std::cout << "funcVector[2](6)=" << res << std::endl;

  divisor++;

  res = funcVector[2](
      6); // here we see that the value divisor was affected by the previos line
  std::cout << "funcVector[2](6)=" << res << std::endl;
}

class Foo {
private:
  int divisor = 5;

public:
  void addFunction(std::vector<std::function<bool(int)>> &funcVector) {
    /**
     * @brief One could asume that by capturing with the default = we would get
     * the provate member divisor, because one can indeed make use of it if the
     * [=] is used. But THE REAL THING IS BEEN CAPUTED IS THE POINTER this. So
     * if the value of the private member is change, this is reflected in the
     * function behaivor. So in this case the explicit capture would have saved
     * us since it sould produce a compile error that the disivor is not a
     * variable
     *
     */
    // funcVector.emplace_back([divisor](int x) { return true; });  // wont
    // compile because divisor is not a variable
    funcVector.emplace_back([=](int x) {
      std::cout << "divisor=" << divisor << std::endl;
      return 0 == (x % divisor);
      /**
       * @brief this code in really is:
       * std::cout << "divisor=" << this->divisor << std::endl;
       * return 0 == (x % this->divisor);
       */
    });
  }

  void setDivisor(int divisor) { this->divisor = divisor; }
};

int main(int argc, char *argv[]) {
  std::vector<std::function<bool(int)>> funcVector;

  {
    int divisor = 5;
    funcVector.emplace_back([&](int x) {
      std::cout << "divisor=" << divisor << std::endl;
      return 0 == (x % divisor);
    });
    funcVector.emplace_back([=](int x) {
      std::cout << "divisor=" << divisor << std::endl;
      return 0 == (x % divisor);
    });

    auto res1 = funcVector[0](5);
    auto res2 = funcVector[0](1);

    std::cout << "funcVector[0](5)=" << res1 << std::endl;
    std::cout << "funcVector[0](1)=" << res2 << std::endl;
  } // here the divisor which was included by reference is deleted so from here
    // on the lamda function has undifined behaivor
  std::cout << "----------default capturing everything by reference----------"
            << std::endl;
  auto res1 = funcVector[0](5);
  auto res2 = funcVector[0](
      1); // this prints divisor=1 and it should be 5. This is very scary I
          // would prefer a segmentation fault actually

  std::cout << "funcVector[0](5)=" << res1 << std::endl;
  std::cout << "funcVector[0](1)=" << res2
            << std::endl; // this is 1 when it should be 0

  std::cout << "----------default capturing everything by value----------"
            << std::endl;
  /**
   * @brief in this case the default capture by value works because it simply
   * creates a copy of the local variable and put it in the enclosure. But this
   * case can be even more dangerous because one can be overconfident that it is
   * self containf when it actually can have hidden dependencies. Look following
   * examples:
   */
  auto res3 = funcVector[1](5);
  auto res4 = funcVector[1](1);

  std::cout << "funcVector[1](5)=" << res3 << std::endl;
  std::cout << "funcVector[1](1)=" << res4 << std::endl;

  // dangerous examples
  // /////////////////////////////////////////////////////////////////////////
  addFunction(funcVector); // look inside function

  Foo f;
  f.addFunction(funcVector);
  funcVector[3](5);
  f.setDivisor(234);
  funcVector[3](1); // this prints 234 as the line before set it

  return 0;
}