#if 0
#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
    using Id = size_t;
    
    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object)
    {
        int current_id = __ID__++;
        int current_prior = 0;
        _dataMap[current_id] = Entity{move(object), current_prior};
        _priorSet.insert({current_prior, current_id});
        return current_id;
    }
    
    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin)
    {
        while (range_begin != range_end) {
            Add(move(*range_begin));
            *ids_begin = (__ID__ - 1);
            ++range_begin;
            ++ids_begin;
        }
    }
    
    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const
    {
        return _dataMap.count(id);
    }
    
    // Получить объект по идентификатору
    const T& Get(Id id) const
    {
        const auto& ent = _dataMap.at(id);
        return ent._obj;
    }
    
    // Увеличить приоритет объекта на 1
    void Promote(Id id)
    {
        int prior = _dataMap.at(id)._prior;
        auto iter = _priorSet.find({prior, id});
        if(iter != _priorSet.end()){
            _priorSet.erase(iter);
            int new_prior = prior + 1;
            _priorSet.insert({new_prior, id});
            
            _dataMap[id]._prior = new_prior;
            
        }
    }
    
    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const
    {
        const auto& p = _priorSet.rbegin();
        const auto& e = _dataMap.at(p->second);
        return {e._obj, p->first};
    }
    
    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax()
    {
        const auto& p = _priorSet.rbegin();
        Id id = p->second;
        int prior = p->first;
        
        _priorSet.erase({prior, id});
        T tmp = move(_dataMap[id]._obj);
        
        _dataMap.erase(id);
        
        return {move(tmp), prior};
    }
    
private:
    struct Entity
    {
        Entity() = default;
        Entity(T&& obj, int prior = 0)
        :_obj(move(obj)),
        _prior(prior)
        {
            
        }
        T _obj;
        int _prior;
    };
    
    std::set<std::pair<int, Id>> _priorSet;
    std::map<Id, Entity> _dataMap;
    
private:
    static size_t __ID__;
};

template<typename T>
size_t PriorityCollection<T>::__ID__ = 0;

class StringNonCopyable : public string {
public:
  using string::string;  // ÐŸÐ¾Ð·Ð²Ð¾Ð»ÑÐµÑ‚ Ð¸ÑÐ¿Ð¾Ð»ÑŒÐ·Ð¾Ð²Ð°Ñ‚ÑŒ ÐºÐ¾Ð½ÑÑ‚Ñ€ÑƒÐºÑ‚Ð¾Ñ€Ñ‹ ÑÑ‚Ñ€Ð¾ÐºÐ¸
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);

  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
    
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
    
    
    
  return 0;
}
#endif
