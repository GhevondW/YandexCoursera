#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <memory>

namespace algo
{

	template<typename T>
	class Queue
	{

		struct Node;

		using Type = T;
		using Data = std::shared_ptr<T>;
		using Next = std::unique_ptr<Node>;
		using Head = Next;
		using Tail = Node*;
		using NRef = Tail;

		struct Node
		{
			Data data{nullptr};
			Next next{nullptr};
		};

	public:
		Queue() = default;
		~Queue() = default;

		auto Empty() const->bool
		{
			return !_size;
		}
		auto Size()	const->size_t
		{
			return _size;
		}

		auto Front() -> T&
		{
			if (_head == nullptr || _head->data.get() == nullptr) {
				throw "invalid operation";
			}
			return *(_head->data);
		}

		auto Front() const -> const T&
		{
			if (_head == nullptr || _head->data.get() == nullptr) {
				throw "invalid operation";
			}
			return *(_head->data);
		}

		auto Back() -> T&
		{
			if (_tail == nullptr || _tail->data.get() == nullptr) {
				throw "invalid operation";
			}
			return *(_tail->data.get());
		}

		auto Back() const -> const T&
		{
			if (_tail == nullptr || _tail->data.get() == nullptr) {
				throw "invalid operation";
			}
			return *(_tail->data);
		}

		auto Push(T value) -> void
		{
			std::unique_ptr<Node> new_node = std::make_unique<Node>();
			new_node->data = std::make_shared<T>(std::move(value));
			if (_head.get() == _tail && _tail == nullptr)
			{
				_head = std::move(new_node);
				_tail = _head.get();
			}
			else {
				_tail->next = std::move(new_node);
				_tail = _tail->next.get();
			}
			++_size;
		}

		auto Pop() -> void
		{
			if (Empty()) throw "invalid operation";
			_head = std::move(_head->next);
			--_size;
		}

	private:
		Head	 _head{nullptr};
		Tail	 _tail{nullptr};
		size_t	 _size{0};
	};
}

#endif // !_QUEUE_H_

