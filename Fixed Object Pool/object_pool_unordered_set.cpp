#if 0
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
#include <memory>
#include <unordered_map>
#include <unordered_set>
using namespace std;

template <class T>
class ObjectPool {
private:
    
//    struct Compare
//    {
//        using is_transparent = void;
//          
//        bool operator()(const unique_ptr<T>& lhs, const unique_ptr<T>& rhs) const {
//            return lhs < rhs;
//        }
//        bool operator()(const unique_ptr<T>& lhs, const T* rhs) const {
//          return less<const T*>()(lhs.get(), rhs);
//        }
//        bool operator()(const T* lhs, const unique_ptr<T>& rhs) const {
//          return less<const T*>()(lhs, rhs.get());
//        }
//    };
    
public:
    
    ObjectPool()
    :_allocated(),
    _deallocated()
    {}
    
    ~ObjectPool()
    {}
    
public:
    T* Allocate()
    {
        if(_deallocated.empty()){
            _deallocated.push(std::make_unique<T>());
        }
        auto ret = move(_deallocated.front());
        _deallocated.pop();
        T* addr = ret.get();
        _allocated.insert(move(ret));
        return addr;
    }
    
    T* TryAllocate()
    {
        return _deallocated.empty() ? nullptr : Allocate();
    }

    void Deallocate(T* object)
    {
        std::unique_ptr<T> tmp{object};
        auto it = _allocated.find(tmp);
        tmp.release();
        if(it != _allocated.end()){
            auto extracted = _allocated.extract(it);
            _deallocated.push(move(extracted.value()));
        }
        else{
            throw invalid_argument{"inv argument"};
        }
    }

private:
    std::unordered_set<std::unique_ptr<T>/*, Compare*/> _allocated;
    std::queue<std::unique_ptr<T>> _deallocated;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
    
  return 0;
}
#endif
