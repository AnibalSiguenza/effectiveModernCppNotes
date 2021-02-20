// this items talks about the risks destroying a thread in joinable status, and
// a non-perfect solution making a thread class which is RAII principles
#include <bits/stdc++.h>

using namespace std::literals;

void foo(std::string name) {
  std::cout << "Running thread i=" << name << std::endl;
  std::this_thread::sleep_for(1s);
}

bool shouldJoin() { return false; }

void badFunction() {
  std::thread t(foo, std::string("badFunction thread"));

  if (shouldJoin()) {
    t.join();
  }
}

class ThreadRAII {
public:
  enum class DtocAction { join, detach };

  ThreadRAII(std::thread &&thread, DtocAction dtocAction)
      : _thread(std::move(thread)), _dtocAction(dtocAction){};
  ~ThreadRAII() {
    if (_thread.joinable()) {
      if (_dtocAction == DtocAction::join) {
        _thread.join();
      } else if (_dtocAction == DtocAction::detach) {
        _thread.detach();
      }
    }
  };

  std::thread &get() { return _thread; }

private:
  std::thread _thread;
  DtocAction _dtocAction;
};

void goodFunction(ThreadRAII::DtocAction daction) {
  ThreadRAII traii(std::thread(foo, "good function"), daction);
}

int main(int argc, char *argv[]) {
  // badFunction();  // this function makes a runtime error: terminate called
  // without an active exception because there is one path in which the thread
  // was not joined

  goodFunction(ThreadRAII::DtocAction::
                   join); // choosing join it will make sure the thread is join
                          // and consequently excecuted before the object is
                          // deleted. Therefor we see the output of the function
  // goodFunction(ThreadRAII::DtocAction::detach);  // choosing the thread can
  // be detached so it is not shurelly excecuted before the program ends. So no
  // output is seen.

  return 0;
}