#ifndef _STACK_H_
#define _STACK_H_

#include <memory>

namespace algo
{

	template<class T>
	class Stack
	{

		struct Node
		{
			T data;
			std::unique_ptr<Node> next{nullptr};
		};

	public:
		Stack() = default;
		~Stack() = default;

	public:

		inline auto Empty() const->bool { return _size == 0; }
		inline auto Size() const->size_t { return _size; }

		auto Push(T value) -> void
		{
			std::unique_ptr<Node> new_node(new Node{ std::move(value), nullptr });
			if (_head == nullptr && _tail == nullptr)
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

		auto Top() -> T&
		{
			if (Empty()) throw "invalid operation";
			return _tail->data;
		}

		auto Pop() -> void
		{
			if (Empty()) throw "invalid operation";
			if (_tail == _head.get())
			{
				_head = std::move(std::unique_ptr<Node>{nullptr});
				_tail = nullptr;
				--_size;
				return;
			}

			Node* prev = _head.get();

			while (true)
			{
				if (prev->next.get() == _tail) {
					break;
				}
				prev = prev->next.get();
			}

			
			prev->next = std::move(std::unique_ptr<Node>(nullptr));
			_tail = prev;
			--_size;

		}

	private:
		std::unique_ptr<Node>	_head{nullptr};
		Node*					_tail{nullptr};
		size_t					_size{0};
	};

}

#endif // !_STACK_H_

