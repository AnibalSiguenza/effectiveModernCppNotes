// this items advices to asume that the move operations are not present, not cheap and not used. This is because many
// non obious conditions can interphere in making this operation faster and used.
#include <bits/stdc++.h>

#include "TestClass.hpp"
#include "TestClassNoExcept.hpp"

int main(int argc, char *argv[]) {
    constexpr int N = 4;

    std::vector<TestClassNoExcept> vtcNoExcept(N, TestClassNoExcept("TestClassNoExcept vector instance"));
    std::vector<TestClass> vtc(N, TestClass("TestClass vector instance"));
    std::array<TestClassNoExcept, N> atc;
    std::fill(atc.begin(), atc.end(), TestClassNoExcept("TestClassNoExcept array instance"));
    std::cout << "------------------End of initialization------------------" << std::endl;

    /**
     * @brief this section demostrates that with a move of the vectors the only thing which is move is the pointer
     * to the first element of the array. But for array the N elements are moved one by one because they are allocated
     * on the stack with out a pointer to move. Which makes that the move operation of vector perform in contant time 
     * complexity while the array performs in lineal time.
     */
    std::cout << "----------------- copy vector no except------------------" << std::endl;
    auto vtcNoExceptCopy = std::move(vtcNoExcept);
    std::cout << "---------------------- copy vector ----------------------" << std::endl;
    auto vtcCopy = std::move(vtc);
    std::cout << "---------------------- copy array -----------------------" << std::endl;
    auto atcCopy = std::move(atc);

    /**
     * @brief this section demostrates that with the push_back you can call N moves or copies. Since the space is 4
     * a new allocations must be done before the elemnt can be appended to the vector. After that the already stored
     * are moved to the new allocation. If the move implementation is no except it will be used. But if it was not
     * declared as such then it will do a copy. 
     */
    std::cout << "--------------- append vector no except -----------------" << std::endl;
    vtcNoExceptCopy.push_back(TestClassNoExcept("new element no except"));
    std::cout << "--------------------- append vector ---------------------" << std::endl;
    vtcCopy.push_back(TestClass("new element"));

    std::cout << "-------------------before main returns-------------------" << std::endl;
    return 0;
}