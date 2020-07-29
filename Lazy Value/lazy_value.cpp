#if 1
#include "test_runner.h"

#include <functional>
#include <string>
using namespace std;

template <typename T>
class LazyValue {
public:
    explicit LazyValue(std::function<T()> init)
    :_fInit(init)
    {
        
    }
    
    bool HasValue() const{ return (bool)_Obj; }
    
    const T& Get() const
    {
        _mObjLock.lock();
        if(!_Obj){
            _Obj = _fInit();
        }
        _mObjLock.unlock();
        return _Obj.value();
    }

private:
    mutable std::optional<T> _Obj;
    const std::function<T()> _fInit;
    mutable std::mutex _mObjLock;
};

void UseExample() {
  const string big_string = "Giant amounts of memory";

  LazyValue<string> lazy_string([&big_string] { return big_string; });

  ASSERT(!lazy_string.HasValue());
  ASSERT_EQUAL(lazy_string.Get(), big_string);
  ASSERT_EQUAL(lazy_string.Get(), big_string);
}

void TestInitializerIsntCalled() {
  bool called = false;

  {
    LazyValue<int> lazy_int([&called] {
      called = true;
      return 0;
    });
  }
  ASSERT(!called);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, UseExample);
  RUN_TEST(tr, TestInitializerIsntCalled);
  return 0;
}
#endif
