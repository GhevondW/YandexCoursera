#if 0
#include "test_runner.h"

#include <cstddef>
#include <utility>

using namespace std;


template <typename T>
class UniquePtr {
public:
    UniquePtr(){ _data = nullptr; }
    UniquePtr(T * ptr)
    :_data(std::move(ptr))
    {}

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&& other) noexcept
    {
        _data = std::move(other._data);
        other._data = nullptr;
    }

    UniquePtr& operator = (const UniquePtr&) = delete;
    UniquePtr& operator = (nullptr_t val)
    {
        _Clear();
        return *this;
    }
    UniquePtr& operator = (UniquePtr&& other)
    {
        _Clear();
        _data = other._data;
        other._data = nullptr;
        return *this;
    }

    ~UniquePtr(){ _Clear(); }

    T& operator * () const { return *_data; }

    T * operator -> () const { return _data; }

    T * Release()
    {
        T* tmp = _data;
        _data = nullptr;
        return tmp;
    }

    void Reset(T * ptr)
    {
        _Clear();
        _data = ptr;
    }

    void Swap(UniquePtr& other)
    {
        T* tmp = _data;
        _data = other._data;
        other._data = tmp;
    }

    T * Get() const { return _data; }

private:

    inline void _Clear(){
        if(_data != nullptr){
            delete _data;
            _data = nullptr;
        }
    }

private:
    T* _data;
};



struct Item {
  static int counter;
  int value;
  Item(int v = 0): value(v) {
    ++counter;
  }
  Item(const Item& other): value(other.value) {
    ++counter;
  }
  ~Item() {
    --counter;
  }
};

int Item::counter = 0;


void TestLifetime() {
  Item::counter = 0;
  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);

    ptr.Reset(new Item);
    ASSERT_EQUAL(Item::counter, 1);
  }
  ASSERT_EQUAL(Item::counter, 0);

  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);

    auto rawPtr = ptr.Release();
    ASSERT_EQUAL(Item::counter, 1);

    delete rawPtr;
    ASSERT_EQUAL(Item::counter, 0);
  }
  ASSERT_EQUAL(Item::counter, 0);
}

void TestGetters() {
  UniquePtr<Item> ptr(new Item(42));
  ASSERT_EQUAL(ptr.Get()->value, 42);
  ASSERT_EQUAL((*ptr).value, 42);
  ASSERT_EQUAL(ptr->value, 42);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLifetime);
  RUN_TEST(tr, TestGetters);
}
#endif
