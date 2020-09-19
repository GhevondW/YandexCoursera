#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <memory>

namespace parallel 
{
	
	template<typename T>
	class queue
	{
		struct node
		{
			std::shared_ptr<T>		_item{nullptr};
			std::unique_ptr<node>	_next{nullptr};
		};
	public:
		queue();
		~queue() = default;

	public:

		auto Push(T value)	-> void;
		auto TryPop()		-> std::shared_ptr<T>;
		auto Empty() const	->bool;

	private:
		std::unique_ptr<node>	_head{nullptr};
		node*					_tail{nullptr};
	};

	template<typename T>
	queue<T>::queue()
		:_head(new node), _tail(_head.get())
	{
		
	}

	template<typename T>
	auto queue<T>::Push(T value) -> void
	{
		std::shared_ptr<T> new_item{ std::make_shared<T>(std::move(value)) };
		std::unique_ptr<node> p{ new node };
		_tail->_item = new_item;
		node* new_tail = p.get();
		_tail->_next = std::move(p);
		_tail = new_tail;
	}

	template<typename T>
	auto queue<T>::TryPop() -> std::shared_ptr<T>
	{
		if (_head.get() == _tail) return std::shared_ptr<T>{nullptr};
		std::shared_ptr<T> ret = std::move(_head->_item);
		std::unique_ptr<node> old_head = std::move(_head);
		_head = std::move(old_head->_next);
		return ret;
	}

	template<typename T>
	auto queue<T>::Empty() const -> bool
	{
		return _head == nullptr && _tail == nullptr;
	}
};

#endif // !_QUEUE_H_

