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

			node(T item)
				:_item(std::move(item))
			{}

			T _item;
			std::unique_ptr<node> _next{nullptr};
		};
	public:
		queue() = default;
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
	auto queue<T>::Push(T value) -> void
	{
		std::unique_ptr<node> new_node{ new node{std::move(value)} };
		node* new_tail = new_node.get();
		if (_tail) {
			_tail->_next = std::move(new_node);
		}
		else {
			_head = std::move(new_node);
		}
		_tail = new_tail;
	}

	template<typename T>
	auto queue<T>::TryPop() -> std::shared_ptr<T>
	{
		if (!_head) return std::shared_ptr<T>(nullptr);
		std::shared_ptr<T> ret = std::make_shared<T>(std::move(_head->_item));
		auto old_head = std::move(_head);
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

