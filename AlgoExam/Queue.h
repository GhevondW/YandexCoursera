#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <deque>

namespace algo
{

	template<class T, class C = std::deque<T>>
	class Queue
	{

        using _DataType = T;
        using _Container = C;

	public:
		Queue() = default;
        Queue(const Queue&) = default;
        Queue(Queue&&) = default;
        ~Queue() = default;

        Queue& operator=(const Queue& other)
        {
            this->_c = other._c;
            return *this;
        }
        
        Queue& operator=(Queue&& other)
        {
            this->_c = std::move(other._c);
            return *this;
        }
        auto Empty() const -> bool { return _c.empty(); }
        auto Size()	const -> size_t { return _c.size(); }
        auto Front() -> T& { return _c.front(); }
        auto Front() const -> const T& { return _c.front(); }
        auto Back() -> T&{ return _c.back(); }
        auto Back() const -> const T& { return _c.back(); }
        auto Push(const T& value) -> void { _c.push_back(value); }
        auto Push(T&& value) -> void { _c.push_back(std::move(value)); }
        auto Pop() -> void { _c.pop_front(); }

	private:
        _Container _c{};
	};
}

#endif // !_QUEUE_H_

