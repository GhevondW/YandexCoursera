#if 1
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
    
public:
    
    ObjectPool()
    :_allocated(),
    _deallocated()
    {}
    
    ~ObjectPool()
    {
        auto curr = _allocated.begin();
        while (curr != _allocated.end()) {
            T* tmp = *curr;
            delete tmp;
            ++curr;
        }
        _allocated.clear();
        while (!_deallocated.empty()) {
            delete _deallocated.front();
            _deallocated.pop();
        }
    };
    
public:
    T* Allocate()
    {
        if(_deallocated.empty()){
            T* n = new T;
            _allocated.insert(n);
            return n;
        }
        T* ret = _deallocated.front();
        _allocated.insert(ret);
        _deallocated.pop();
        return ret;
    }
    
    T* TryAllocate()
    {
        return _deallocated.empty() ? nullptr : Allocate();
    }

    void Deallocate(T* object)
    {
        auto it = _allocated.find(object);
        if(it != _allocated.end()){
            T* tmp = *it;
            _deallocated.push(tmp);
            _allocated.erase(it);
        }
        else{
            throw invalid_argument{"inv argument"};
        }
    }

private:
    std::set<T*> _allocated;
    std::queue<T*> _deallocated;
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
