#if 0
#include "test_runner.h"
#include <iostream>

using namespace std;

template<class T>
class Table
{
    using Data = std::vector<std::vector<T>>;
public:
    Table(size_t width = 0, size_t height = 0)
    :_width(width),
    _height(height)
    {
        Resize(_width, _height);
    }
    
public:
    
    const std::pair<size_t, size_t> Size() const{
        return std::make_pair(_width, _height);
    }
    
    const std::vector<T>& operator[](size_t index) const
    {
        return _data[index];
    }

    std::vector<T>& operator[](size_t index)
    {
        return _data[index];
    }
    
    void Resize(size_t w, size_t h){
        _width = w;
        _height = h;
        _data.resize(_width);
        for (std::vector<T>& vect : _data) {
            vect.resize(_height);
        }
    }
    
private:
    size_t _width;
    size_t _height;
    Data _data;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
#endif
