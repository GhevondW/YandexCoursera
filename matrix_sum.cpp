#if 1
#include "test_runner.h"
#include <vector>
#include <future>
#include <algorithm>
#include <numeric>
using namespace std;

template<class Iter>
class IteratorRange
{
public:
    IteratorRange(Iter b, Iter e)
    :_begin(b), _end(e){}
    
    auto begin() { return _begin; }
    auto end() { return _end; }
    
    auto begin() const { return _begin; }
    auto end() const { return _end; }
    
    size_t size() const { return std::distance(_begin, _end); }
    
private:
    Iter _begin;
    Iter _end;
};

template <typename Iterator>
class Paginator {
    
public:
    
    Paginator(Iterator begin, Iterator end, size_t size)
    :_pageSize(size)
    {
        auto d = std::distance(begin, end);
        int count = d / size;
        Iterator curr = begin;
        while (count != 0) {
            _pages.emplace_back(curr, curr + size);
            curr = curr + size;
            --count;
        }
        if(d % size != 0){
            _pages.emplace_back(curr, end);
        }
    }
    
    size_t size() const { return _pages.size(); }
    
    auto begin() { return _pages.begin(); }
    auto end() { return _pages.end(); }
    
private:
    std::vector<IteratorRange<Iterator>> _pages;
    size_t _pageSize;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator{c.begin(), c.end(), page_size};
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    
    std::vector<std::future<size_t>> results;
    
    for (auto page : Paginate(matrix, 2000)) {
        results.push_back(std::async([page]()->size_t
        {
            size_t res = 0;
            for (auto& item: page) {
                res += std::accumulate(begin(item), end(item), 0);
            }
            return res;
        }));
    }
    
    size_t result = 0;
    for (auto& f : results) {
        result += f.get();
    }
    return result;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}
#endif
