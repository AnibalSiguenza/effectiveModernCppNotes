// This items talks about the Impl idiom and how to correctly implemented using unique_ptr
// the Impl idiom is used to optimize compilation time and reduce the dependencies of the header.
// in this example we only include the item22Class.hpp header to the main. And it internally in the
// item22Class.cpp implementation file there are the dependencies to <memory> header and TestClassNoExcept.hpp
// this makes the dependencies local, so if something is changed in memory or in TestClassNoExcept.hpp, the only
// unit which would need to recompile is the item22Class.o, optimizing the compilation time
#include "item22Class.hpp"

int main(int argc, char *argv[]) {
    Popo p1;

    Popo p2(std::move(p1));
    // p1.hello();  //this makes a segmentation fault beacuse the pointer of the impl was invalidated in the move operation

    Popo p3;
    p3 = std::move(p2);

    p1 = p3;
    Popo p4(p1);

    return 0;
}