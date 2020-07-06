#include "Common.h"
#include <list>
#include <unordered_map>
#include <queue>
#include <mutex>

using namespace std;

class LruCache : public ICache {
    using CacheIter = std::list<BookPtr>::iterator;
    using CacheConstIter = std::list<BookPtr>::const_iterator;
public:
    LruCache(shared_ptr<IBooksUnpacker> books_unpacker, const Settings& settings)
    :_booksUnpacker(books_unpacker),
    _settings(settings)
    {
      // реализуйте метод
    }
    
    BookPtr GetBook(const string& book_name) override {
        std::lock_guard<std::mutex> lock(_lock);
        if(_indexName.find(book_name) != end(_indexName)){
            auto iter = _indexName[book_name];
            _cache.splice(end(_cache), _cache, iter);
            return *iter;
        }
        
        BookPtr book = _booksUnpacker->UnpackBook(book_name);
        size_t book_mem = book->GetContent().size();
        size_t max_mem = _settings.max_memory;
        
        if(book_mem > max_mem) return book;
        
        _ClearCahce(book_mem);
        
        _cache.push_back(book);
        auto last = std::prev(_cache.end());
        _indexName.insert({book_name, last});
        _memoryUsed  += book->GetContent().size();
        
        return _cache.back();
    }
    
private:
    
    void _ClearCahce(size_t mem){
        
        while (true) {
            size_t free_mem = _settings.max_memory - _memoryUsed;
            auto iter = begin(_cache);
            
            if(free_mem >= mem || iter == end(_cache)) return;
            
            size_t curr_size = (*iter)->GetContent().size();
            _memoryUsed -= curr_size;
            _indexName.erase((*iter)->GetName());
            _cache.erase(iter);
        }
        
    }
    
private:
    
    shared_ptr<IBooksUnpacker> _booksUnpacker;
    const Settings _settings;
    
    std::list<BookPtr> _cache{};
    std::unordered_map<std::string, CacheIter> _indexName{};
    
    int _memoryUsed{0};
    
    std::mutex _lock;
    
};


unique_ptr<ICache> MakeCache(shared_ptr<IBooksUnpacker> books_unpacker, const ICache::Settings& settings) {
    return std::make_unique<LruCache>(move(books_unpacker), settings);
}
