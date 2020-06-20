#if 0
#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <list>

using namespace std;

using ID = string;

struct Record {
    string id;
    string title;
    string user;
    int timestamp;
    int karma;
};
    
class Database {
    
    using DataIter = std::list<Record>::iterator;
    using DataConstIter = std::list<Record>::const_iterator;
    using IndexKarmaConstIter = std::multimap<int, DataConstIter>::const_iterator;
    using IndexTimeConstIter = std::multimap<int, DataConstIter>::const_iterator;
    using IndexUserConstIter = std::multimap<string, DataConstIter>::const_iterator;
    
public:
    
    Database() = default;
    
    bool Put(const Record& record);
    const Record* GetById(const string& id) const;
    bool Erase(const string& id);
    
    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const;
    
    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const;
    
    template <typename Callback>
    void AllByUser(const string& user, Callback callback) const;
    
private:
    
    struct Refs
    {
        IndexKarmaConstIter indexKarma;
        IndexTimeConstIter indexTime;
        IndexUserConstIter indexUser;
    };
    
private:
    
    std::list<Record> _Data;
    std::unordered_map<ID, DataConstIter> _IdToData;
    std::multimap<int, DataConstIter> _KarmaToData;
    std::multimap<int, DataConstIter> _TimeToData;
    std::multimap<string, DataConstIter> _UserToData;
    std::unordered_map<ID, Refs> _IterRefs;
    
};

bool Database::Put(const Record& record)
{
    if(!_IdToData.count(record.id)){
        
        _Data.push_front(record);
        DataConstIter data_iter = begin(_Data);
        
        _IdToData.insert({record.id, data_iter});
        
        Refs refs;
        
        refs.indexKarma = _KarmaToData.insert({record.karma, data_iter});
        refs.indexTime = _TimeToData.insert({record.timestamp, data_iter});
        refs.indexUser = _UserToData.insert({record.user, data_iter});
        
        _IterRefs.insert({record.id, move(refs)});
        
        return true;
    }
    return false;
}

const Record* Database::GetById(const string& id) const
{
    if(_IdToData.count(id)){
        return &(*_IdToData.at(id));
    }
    return nullptr;
}

bool Database::Erase(const string& id)
{
    if(_IdToData.count(id)){
        
        Refs& r = _IterRefs[id];
        
        _UserToData.erase(r.indexUser);
        _KarmaToData.erase(r.indexKarma);
        _TimeToData.erase(r.indexTime);
        
        _IterRefs.erase(id);
        
        _Data.erase(_IdToData.at(id));
        
        _IdToData.erase(id);
        
        return true;
    }
    return false;
}

template <typename Callback>
void Database::RangeByTimestamp(int low, int high, Callback callback) const
{
    auto c = _TimeToData.lower_bound(low);
    auto d = _TimeToData.upper_bound(high);
    while (c != d) {
        if(!callback(*(c->second))){
            return;
        }
        ++c;
    }
}

template <typename Callback>
void Database::RangeByKarma(int low, int high, Callback callback) const
{
    auto c = _KarmaToData.lower_bound(low);
    auto d = _KarmaToData.upper_bound(high);
    while (c != d) {
        if(!callback(*(c->second))){
            return;
        }
        ++c;
    }
}

template <typename Callback>
void Database::AllByUser(const string& user, Callback callback) const
{
    auto range = _UserToData.equal_range(user);
    for (auto it = range.first; it != range.second; ++it) {
        if(!callback(*(it->second))){
            return;
        }
    }
}

void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;
        RUN_TEST(tr, TestRangeBoundaries);
        RUN_TEST(tr, TestSameUser);
        RUN_TEST(tr, TestReplacement);
    
    
  return 0;
}
#endif
