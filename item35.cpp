// this items recomends to prefer the async implementation over the threads.
// This is simpler conseptually and gives better exeption handeling, as well as
// an easier way to obtain the return values. note to compile: g++ item35.cpp
// -Wall -o a.out -pthread -std=c++17  && ./a.out
#include <bits/stdc++.h>

#include <exception> // std::exception

int doAsyncWork(int throwing) {
  if (throwing == 1) {
    throw(std::bad_exception());
  }

  return 0;
}

int main(int argc, char *argv[]) {
  std::vector<std::thread> vTh;
  std::vector<std::future<int>> vFut;

  for (size_t i = 0; i < 5; i++) {
    vTh.emplace_back(std::thread(doAsyncWork, 0));
    vFut.emplace_back(std::async(doAsyncWork, 0));
  }

  vFut.emplace_back(std::async(doAsyncWork, 1));
  for (auto &fut : vFut) {
    try {
      std::cout << fut.get()
                << std::endl; // the function get obtains the return value and
                              // the try block can catch the exeption
    } catch (const std::exception &e) {
      std::cout << "Catching exception:" << std::endl;
      std::cout << e.what() << '\n';
    }
  }

  vTh.emplace_back(
      std::thread(doAsyncWork, 1)); // uncomment to see the program will crash
  for (auto &t : vTh) {
    try {
      t.join(); // there is no way to obtain the return value and the exception
                // is not catch making the program crash
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
    }
  }

  return 0;
}