// this item explains that the default launch policy for async can be either
// async or deffered and this can have serios consequences if not handle
// correctly note to compile: g++ item36.cpp -Wall -o a.out -pthread -std=c++17
// && ./a.out
#include <bits/stdc++.h>

using namespace std::literals;

void foo(int i) {
  printf("running thread with i=%i\n", i);
  std::this_thread::sleep_for(1s);
  printf("finish thread with i=%i\n", i);
}

int main(int argc, char *argv[]) {
  {
    std::cout << "**********************default**********************"
              << std::endl;
    std::vector<std::future<void>> vFut;

    for (size_t i = 0; i < 4; i++) {
      /**
       * We are calling with default for which the launch policy of the standart
       * decides which launch policy use in my experiments it was always asyn,
       * but hte book says that with heavy loads it can call deferred
       *
       */
      vFut.emplace_back(std::async(foo, i + 1));
    }

    std::for_each(vFut.begin(), vFut.end(),
                  [](auto &elem) { elem.get(); }); // for syncronization
  }
  {
    std::cout << "**********************deferred**********************"
              << std::endl;
    std::vector<std::future<void>> vFut;

    for (size_t i = 0; i < 4; i++) {
      // since we use deferred policy the threads are created but not excecuted
      // until we run a get
      vFut.emplace_back(std::async(std::launch::deferred, foo, i + 1));
    }

    // in this case the function is called until the get() is called so it will
    // have sequential behaivor
    std::for_each(vFut.begin(), vFut.end(),
                  [](auto &elem) { elem.get(); }); // for syncronization
  }
  {
    std::cout << "**********************async**********************"
              << std::endl;
    std::vector<std::future<void>> vFut;

    for (size_t i = 0; i < 4; i++) {
      // this launch policy inmediately runs the function so we can see all
      // calls of running in parallel
      vFut.emplace_back(std::async(std::launch::async, foo, i + 1));
    }

    std::for_each(vFut.begin(), vFut.end(),
                  [](auto &elem) { elem.get(); }); // for syncronization
  }

  std::cout << "**********************wait experiment**********************"
            << std::endl;
  // the risk is if it is used a defered one could cause a dead lock as follows

  // auto future = std::async(std::launch::deferred, foo, 0);
  auto future = std::async(std::launch::async, foo, 0);

  // next line is a dead lock for a deferred future because a defered future
  // will never have ready status
  while (future.wait_for(100ms) != std::future_status::ready) {
    std::cout << "Waiting ...." << std::endl;
  }
  std::cout << "Finish waiting" << std::endl;

  std::cout << "**********************correct waiting**********************"
            << std::endl;
  /**
   * In this sections it is showed the correct way to wait for all cases. This
   * must be done if there is a while wait for in any default instance of async.
   * Or ALWAYS put the launch policy
   *
   */
  auto deferedFuture = std::async(std::launch::deferred, foo, 0);

  if (deferedFuture.wait_for(0s) == std::future_status::deferred) {
    std::cout << "The thread is deferred" << std::endl;
    deferedFuture.get();
  } else {
    while (deferedFuture.wait_for(100ms) != std::future_status::ready) {
      std::cout << "Waiting ...." << std::endl;
    }
    std::cout << "Finish waiting" << std::endl;
  }

  return 0;
}