#ifndef _STACK_H_
#define _STACK_H_

#include <deque>

namespace algo
{

	template<class T, class C = std::deque<T>>
	class Stack
	{
        using _DataType = T;
        using _Container = C;
	public:
		Stack() = default;
        Stack(const Stack&) = default;
        Stack(Stack&&) = default;
		~Stack() = default;

        Stack& operator=(const Stack& other)
        {
            this->_c = other._c;
            return *this;
        }
        
        Stack& operator=(Stack&& other)
        {
            this->_c = std::move(other._c);
            return *this;
        }
        
	public:

        inline auto Empty() const -> bool { return _c.empty(); }
        inline auto Size() const -> size_t { return _c.size(); }
        auto Push(const T& value) -> void { _c.pysh_back(value); }
        auto Push(T&& value) -> void { _c.push_back(std::move(value)); }
        auto Top() -> T& { return _c.back(); }
        auto Pop() -> void { _c.pop_back(); }

	private:
        _Container _c{};
	};

}

#endif // !_STACK_H_

