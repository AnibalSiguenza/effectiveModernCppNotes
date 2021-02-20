// this items gives the details of the special member functions of the class.
// Which actions invalidates the default constucture this item is quite complex
// and relevant! But if you want a be safe it's simple if you declare a specific
// member function just declare ALL of them constructor, distructor, copy
// constructor, copy assign, move constructor and move assign.
#include <bits/stdc++.h>

#include "TestClass.hpp"

/**
 * @brief This class is completely default, by declaring, coping and moving it
 * will use the correponding constructure of all its members in this case of the
 * TestClass.
 *
 */
class DefaultClass {
private:
  TestClass _tc;

public:
};

/**
 * @brief This class has a special constructor declared, which makes that the
 * default constructor gets errased.
 *
 */
class SpecialContructorClass {
private:
  TestClass _tc;

public:
  SpecialContructorClass(std::string name) : _tc(name) {}
};

/**
 * @brief This class has a special copy constructor declared, this errases the
 * default constructor, the move constructor and move assign
 */
class SpecialCopyClass {
private:
  TestClass _tc;

public:
  SpecialCopyClass() =
      default; // with the default keyword, one indicates to use the default
               // constructor even if it should have been erased

  SpecialCopyClass(const SpecialCopyClass &x) : _tc(x._tc) {
    std::cout << "SpecialCopyClass copy constructor" << std::endl;
  }
};

/**
 * @brief This class has a special copy assign declared. This errases the move
 * constructor and move assign
 */
class SpecialAssignClass {
private:
  TestClass _tc;

public:
  const SpecialAssignClass &operator=(const SpecialAssignClass &x) {
    _tc = x._tc;
    std::cout << "SpecialAssignClass copy assign" << std::endl;
    return *this;
  }
};

/**
 * @brief This class has a special move constructor declared. It errases
 * everything execpt the destructor
 */
class SpecialMoveClass {
private:
  TestClass _tc;

public:
  SpecialMoveClass() =
      default; // with the default keyword, one indicates to use the default
               // constructor even if it should have been erased

  SpecialMoveClass(const SpecialMoveClass &&x) : _tc(std::move(x._tc)) {
    std::cout << "SpecialMoveClass move constructor" << std::endl;
  }
};

/**
 * @brief This class has a special move assign declared. It errases everything
 * execpt the destructor and default constructor
 */
class SpecialMoveAssignClass {
private:
  TestClass _tc;

public:
  const SpecialMoveAssignClass &operator=(const SpecialMoveAssignClass &&x) {
    _tc = std::move(x._tc);
    std::cout << "SpecialMoveAssignClass move assign" << std::endl;
    return *this;
  }
};

/**
 * @brief This class has a special move assign declared. It errases everything
 * execpt the destructor and default constructor
 */
class SpecialDistructorClass {
private:
  TestClass _tc;

public:
  ~SpecialDistructorClass() {
    std::cout << "SpecialDistructorClass" << std::endl;
  }
};

int main(int argc, char *argv[]) {
  // In this example one can see all implicit member functions created
  std::cout << "======================DefaultClass======================"
            << std::endl;
  DefaultClass defaultIntance; // calls TestClass default contructor
  DefaultClass copyIntance =
      defaultIntance;           // calls TestClass default copy constructor
  copyIntance = defaultIntance; // calls TestClass default copy assign
  DefaultClass copyContruct =
      std::move(defaultIntance); // calls TestClass default move contructor
  defaultIntance =
      std::move(copyIntance); // calls TestClass default move assign
  std::cout << std::endl;

  std::cout
      << "======================SpecialContructorClass======================"
      << std::endl;
  // This is the result when there is a special constructure declared
  // SpecialContructorClass defaultIntance2;                   // ERROR because
  // default was errased when the second construcor was created
  SpecialContructorClass defaultIntance2(
      "Anibal"); // We are forced to use the special contructor we created
  SpecialContructorClass copyIntance2 =
      defaultIntance2;            // calls TestClass default copy constructor
  copyIntance2 = defaultIntance2; // calls TestClass default copy assign
  SpecialContructorClass copyContruct2 =
      std::move(defaultIntance2); // calls TestClass default move contructor
  defaultIntance2 =
      std::move(copyIntance2); // calls TestClass default move assign
  std::cout << std::endl;

  /**
   * The most dangerous cases are the next 2 in which one could think that the
   * move operators were generated since the compiler will produce an error, BUT
   * it just silently remplaces the move operators by the copy operators. This
   * can have strong performance implication.
   */
  std::cout << "======================SpecialCopyClass======================"
            << std::endl;
  // This is the result when there is a special copy constructure declared
  SpecialCopyClass defaultIntance3; // No error thanks to default keyword
  SpecialCopyClass copyIntance3 =
      defaultIntance3;            // calls the special copy constructor
  copyIntance3 = defaultIntance3; // calls TestClass default copy assign
  SpecialCopyClass copyContruct3 =
      std::move(defaultIntance3); // NO ERROR, BUT IT CALLS COPY CONSTRUCTOR
  defaultIntance3 =
      std::move(copyIntance3); // NO ERROR, BUT IT CALLS COPY ASSIGN
  std::cout << std::endl;
  std::cout << "======================SpecialAssignClass======================"
            << std::endl;
  // This is the result when there is a special copy assign declared
  SpecialAssignClass defaultIntance4; // calls TestClass default constructor
  SpecialAssignClass copyIntance4 =
      defaultIntance4;            // calls TestClass default copy constructor
  copyIntance4 = defaultIntance4; // calls the special copy assign
  SpecialAssignClass copyContruct4 =
      std::move(defaultIntance4); // NO ERROR, BUT IT CALLS COPY CONSTRUCTOR
  defaultIntance4 =
      std::move(copyIntance4); // NO ERROR, BUT IT CALLS COPY ASSIGN
  std::cout << std::endl;

  std::cout << "======================SpecialMoveClass======================"
            << std::endl;
  // This is the result when there is a special copy assign declared
  SpecialMoveClass defaultIntance5; //  No error thanks to default keyword
  // SpecialMoveClass copyIntance5 = defaultIntance5;              // ERROR
  // because copy constructor was errased copyIntance5 = defaultIntance5; //
  // ERROR because copy assign was errased
  SpecialMoveClass copyContruct5 = std::move(
      defaultIntance5); // calls SpecialMoveClass special move contructor
  // defaultIntance5 = std::move(copyContruct5);                   // ERROR
  // because move assign and copy assign were errased
  std::cout << std::endl;

  std::cout
      << "======================SpecialMoveAssignClass======================"
      << std::endl;
  // This is the result when there is a special copy assign declared
  SpecialMoveAssignClass defaultIntance6; // calls TestClass default constructor
  // SpecialMoveAssignClass copyIntance6 = defaultIntance6;              //
  // ERROR because copy constructor was errased copyIntance6 = defaultIntance6;
  // // ERROR because copy assign was errased SpecialMoveAssignClass
  // copyContruct6 = std::move(defaultIntance6);  // ERROR because move
  // constructor and copy constructor were errased
  defaultIntance6 =
      std::move(defaultIntance6); // calls SpecialMoveClass special move assign
  std::cout << std::endl;

  std::cout
      << "======================SpecialDistructorClass======================"
      << std::endl;
  // This is the result when there is a special copy assign declared
  SpecialDistructorClass defaultIntance7; // calls TestClass default constructor
  SpecialDistructorClass copyIntance7 =
      defaultIntance7;            // calls TestClass default copy constructor
  copyIntance7 = defaultIntance7; // calls TestClass default copy assign
  SpecialDistructorClass copyContruct7 =
      std::move(defaultIntance7); // NO ERROR, BUT IT CALLS COPY CONSTRUCTOR
  defaultIntance7 =
      std::move(defaultIntance7); // NO ERROR, BUT IT CALLS COPY ASSIGN
  std::cout << std::endl;

  return 0;
}