#ifndef _ALGO_LIST_H_
#define _ALGO_LIST_H_

#include <memory>

namespace algo
{
	template<typename T>
	class List
	{
		struct Node
		{
			std::shared_ptr<T> data{nullptr};
			std::unique_ptr<Node> next{nullptr};
		};

	public:

		struct Printer
		{
			void operator()(const List<T>& ref) const
			{
				if (!ref.Empty()) {
					Node* head = ref._head.get();
					while (head && head->data)
					{
						std::cout << *head->data << std::endl;
						head = head->next.get();
					}
				}
			}
		};

		class Iterator
		{
			friend class List;
		private:
			explicit Iterator(Node* ref)
				:_ref(ref)
			{}
		public:
			Iterator() = default;
			Iterator(const Iterator& other) = default;
			Iterator(Iterator&& other) :_ref(other._ref) { other._ref = nullptr; }
			Iterator& operator=(const Iterator& other) = default;
			Iterator& operator=(Iterator&& other) 
			{
				_ref = other._ref;
				other._ref = nullptr;
				return *this;
			}
			~Iterator() = default;

			bool operator==(const Iterator& other)
			{
				return this->_ref == other._ref;
			}

			Iterator& operator++()       // Prefix increment operator.
			{
				if (_ref) {
					_ref = _ref->next.get();
				}
				return *this;
			}
			
			Iterator operator++(int)     // Postfix increment operator.
			{
				if (_ref) {
					Iterator newIter{_ref};
					_ref = _ref->next.get();
					return newIter;
				}
				return Iterator{nullptr};
			}

			T& operator*()
			{
				if (!_ref) throw "invalid operation";
				if (!_ref->data.get()) throw "invalid operation";
				return *_ref->data;
			}

			Iterator& operator--() = delete;       // Prefix decrement operator.
			Iterator operator--(int) = delete;     // Postfix decrement operator.

		private:
			Node* _ref{nullptr};
		};

		//friend Printer;

	public:
		List()
			:_head(std::make_unique<Node>()),
			_size(0)
		{}
		~List() = default;

		inline size_t Size() const noexcept { return _size; }
		inline bool Empty() const noexcept { return _size == 0; }

		void PushBack(T value)
		{
			++_size;
			std::shared_ptr<T> new_data{ std::make_shared<T>(std::move(value)) };
			if (_head->data == nullptr)
			{
				_head->data = std::move(new_data);
				return;
			}

			Node* ref = _head.get();
			while (ref->next != nullptr)
			{
				ref = ref->next.get();
			}

			ref->next = std::make_unique<Node>();
			ref->next->data = std::move(new_data);
		}
		
		auto Find(const T& value) -> Iterator
		{
			if (Empty()) return Iterator{};
			Node* ref = _head.get();
			while (ref != nullptr)
			{
				if (*ref->data == value) {
					return Iterator{ ref };
				}
				ref = ref->next.get();
			}
			return Iterator{ nullptr };
		}

		auto Insert(Iterator position, T value) -> bool
		{
			if (position._ref != nullptr) {
				++_size;
				std::shared_ptr<T> new_data{ std::make_shared<T>(std::move(value)) };

				Node* current = position._ref;
				std::unique_ptr<Node> current_next = std::move(current->next);

				current->next = std::make_unique<Node>();
				current->next->data = std::move(new_data);
				current->next->next = std::move(current_next);
				return true;
			}
			return false;
		}

		auto Delete(Iterator position) -> bool
		{
			if (position._ref != nullptr && _size > 0) {
				--_size;
				Node* current = position._ref;
				std::unique_ptr<Node> current_next = std::move(current->next);
				current->next = std::move(current_next->next);
				return true;
			}
			return false;
		}

		auto PopFront() -> bool
		{
			if (_head->data.get() != nullptr && _size > 0) {
				--_size;
				std::unique_ptr<Node> next = move(_head->next);
				_head = std::move(next);
				return true;
			}
			return false;
		}

	private:
		std::unique_ptr<Node>	_head{nullptr};
		size_t					_size{};
	};

	


}



#endif // !_ALGO_LIST_H_

