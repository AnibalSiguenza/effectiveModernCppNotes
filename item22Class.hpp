#include <memory>

class Popo {
   private:
    // here the incomplete type Impl is created and we can create a pointer to that type
    struct Impl;
    std::unique_ptr<Impl> impl;

   public:
    Popo();

    // function must be only declaread here and not implemented since the header depencencies would not let us correctly implement it in this part
    Popo(Popo&& rhs) noexcept;
    Popo& operator=(Popo&& rhs) noexcept;

    Popo(const Popo& rhs) noexcept;
    Popo& operator=(const Popo& rhs) noexcept;

    void hello();

    ~Popo();
};
