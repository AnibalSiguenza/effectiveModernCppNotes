// This items talks about the risk of creating an thread unsafe function which
// appears to be safe
#include <bits/stdc++.h>

class NoThreadSafe {
private:
  mutable double cache{0};
  mutable bool isCacheValid{false};

public:
  NoThreadSafe(){};
  ~NoThreadSafe(){};

  /**
   * @brief Get the Data object. This function appears to be thread safe since
   * it is const which could suggest it is read only. But since we have a
   * mutable cache data it is really not. Because we are changing the inside.
   */
  double getData() const {
    if (isCacheValid) {
      return cache;
    } else {
      cache = 76543;
      isCacheValid = true;
      return cache;
    }
  }
};

class ThreadSafe {
private:
  mutable double cache{0};
  mutable bool isCacheValid{false};
  mutable std::mutex m;

public:
  ThreadSafe(){};
  ~ThreadSafe(){};

  /**
   * @brief Get the Data object. This function is thread safe since it added a
   * lock and mutex to protect the relevant section.
   */
  double getData() const {
    std::lock_guard<std::mutex> g(m);
    if (isCacheValid) {
      return cache;
    } else {
      cache = 76543;
      isCacheValid = true;
      return cache;
    }
  }
};

int main(int argc, char *argv[]) {
  NoThreadSafe nts;

  auto data = nts.getData();
  std::cout << "data=" << data << std::endl;

  ThreadSafe ts;

  auto data2 = ts.getData();
  std::cout << "data2=" << data2 << std::endl;

  return 0;
}