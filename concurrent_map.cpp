#if 1
#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <random>
#include <future>
using namespace std;

template <typename K, typename V>
class ConcurrentMap {
public:
    static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

    struct Access {
      V& ref_to_value;
    };

    explicit ConcurrentMap(size_t bucket_count)
    :_map(),
    _mapLock(bucket_count),
    _nBucketCount(bucket_count)
    {
        
    }

    Access operator[](const K& key){ return {_map[key]}; }

    map<K, V> BuildOrdinaryMap(){ return {}; }
    
private:
    
    std::map<K, V> _map{};
    std::vector<std::mutex> _mapLock{};
    size_t _nBucketCount{};
    
public:
    static const int _MIN_INT;
    static const int _MAX_INT;
    static const unsigned long long _KEY_COUNT;
};

template <typename K, typename V>
const int ConcurrentMap<K, V>::_MIN_INT = INT_MIN;
template <typename K, typename V>
const int ConcurrentMap<K, V>::_MAX_INT = INT_MAX;
template <typename K, typename V>
const unsigned long long ConcurrentMap<K, V>::_KEY_COUNT = (1 << 32);

void RunConcurrentUpdates(
    ConcurrentMap<int, int>& cm, size_t thread_count, int key_count
) {
  auto kernel = [&cm, key_count](int seed) {
    vector<int> updates(key_count);
    iota(begin(updates), end(updates), -key_count / 2);
    shuffle(begin(updates), end(updates), default_random_engine(seed));

    for (int i = 0; i < 2; ++i) {
      for (auto key : updates) {
        cm[key].ref_to_value++;
      }
    }
  };

  vector<future<void>> futures;
  for (size_t i = 0; i < thread_count; ++i) {
    futures.push_back(async(kernel, i));
  }
}

void TestConcurrentUpdate() {
  const size_t thread_count = 3;
  const size_t key_count = 50000;

  ConcurrentMap<int, int> cm(thread_count);
  RunConcurrentUpdates(cm, thread_count, key_count);

  const auto result = cm.BuildOrdinaryMap();
  ASSERT_EQUAL(result.size(), key_count);
  for (auto& [k, v] : result) {
    AssertEqual(v, 6, "Key = " + to_string(k));
  }
}

void TestReadAndWrite() {
  ConcurrentMap<size_t, string> cm(5);

  auto updater = [&cm] {
    for (size_t i = 0; i < 50000; ++i) {
      cm[i].ref_to_value += 'a';
    }
  };
  auto reader = [&cm] {
    vector<string> result(50000);
    for (size_t i = 0; i < result.size(); ++i) {
      result[i] = cm[i].ref_to_value;
    }
    return result;
  };

  auto u1 = async(updater);
  auto r1 = async(reader);
  auto u2 = async(updater);
  auto r2 = async(reader);

  u1.get();
  u2.get();

  for (auto f : {&r1, &r2}) {
    auto result = f->get();
    ASSERT(all_of(result.begin(), result.end(), [](const string& s) {
      return s.empty() || s == "a" || s == "aa";
    }));
  }
}

void TestSpeedup() {
  {
    ConcurrentMap<int, int> single_lock(1);

    LOG_DURATION("Single lock");
    RunConcurrentUpdates(single_lock, 4, 50000);
  }
  {
    ConcurrentMap<int, int> many_locks(100);

    LOG_DURATION("100 locks");
    RunConcurrentUpdates(many_locks, 4, 50000);
  }
}

int main() {
  TestRunner tr;
//  RUN_TEST(tr, TestConcurrentUpdate);
//  RUN_TEST(tr, TestReadAndWrite);
//  RUN_TEST(tr, TestSpeedup);
    
    std::cout<<ConcurrentMap<int, int>::_KEY_COUNT<<std::endl;
    //18446744071562067968
    //18446744071562067968
}
#endif
