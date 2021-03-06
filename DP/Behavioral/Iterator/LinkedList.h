#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <memory>

#define _ll LinkedList

namespace algo
{
	template<typename T>
	class LinkedList
	{
		struct Node;
		struct Iterator;

		using DataType	= T;
		using NodeRef	= Node*;
		using Data		= std::shared_ptr<DataType>;
		using ConstIter = const Iterator;
		using Iter		= Iterator;

		struct Node
		{
			Data						data{nullptr};
			std::unique_ptr<Node>		next{nullptr};
			NodeRef						prev{nullptr};

			Node() = default;
		};

		struct Iterator
		{
			friend class LinkedList<T>;
		public:
			Iterator() = default;
			explicit Iterator(NodeRef ref)
				:_node(ref)
			{}
			Iterator(const Iterator&) = default;
			~Iterator() = default;
			Iterator(Iterator&& other)
				:_node(other._node)
			{
				other._node = nullptr;
			}

			Iterator& operator=(const Iterator& other) = default;
			Iterator& operator=(Iterator&& other)
			{
				if (&other != this) {
					_node = other._node;
					other._node = nullptr;
				}
				return *this;
			}

			Iterator& operator++()
			{
				_node = _node->next.get();
				return *this;
			}

			Iterator operator++(int)
			{
				NodeRef ref = _node;
				_node = _node->next.get();
				return Iterator{ref};
			}

			Iterator& operator--()
			{
				_node = _node->prev.get();
				return *this;
			}

			Iterator operator--(int)
			{
				NodeRef ref = _node;
				_node = _node->prev;
				return Iterator{ ref };
			}

			NodeRef operator &()
			{
				return _node;
			}

			DataType& operator *()
			{
				if (_node != nullptr) {
					return *(_node->data.get());
				}
				throw "invalid operation";
			}

			bool operator==(const Iterator& other) const
			{
				return _node == other._node;
			}

			bool operator!=(const Iterator& other) const
			{
				return !((*this) == other);
			}

			operator bool() const
			{
				return _node != nullptr;
			}

		private:
			NodeRef _node{nullptr};
		};

	public:
		LinkedList();
		LinkedList(const LinkedList& other);
		LinkedList(LinkedList&& other);
		~LinkedList() = default;

		auto Size() const						-> size_t;
		auto Empty() const						-> bool;
		auto PushBack(DataType value)			-> Iterator;
		auto PushFront(DataType value)			-> Iterator;
		auto PopBack()							-> Data;
		auto PopFront()							-> Data;
		auto InsertBefore(ConstIter, DataType)	-> std::pair<bool, Iterator>;
		auto InsertAfter(ConstIter, DataType)	-> std::pair<bool, Iterator>;
		auto Delete(ConstIter)					-> bool;
		auto Begin()							-> Iterator;
		auto End()								-> Iterator;
		auto Begin() const						-> ConstIter;
		auto End() const						-> ConstIter;

		LinkedList& operator=(const LinkedList& other);
		LinkedList& operator=(LinkedList&& other);

	private:

		auto _AddNode(bool back = true)			-> void;
		auto _InsertAfter(ConstIter, DataType)  ->std::pair<bool, Iterator>;

	private:
		std::unique_ptr<Node>	_head{nullptr};
		NodeRef					_tail{nullptr};
		size_t					_size{0};
	};

	template<typename T>
	_ll<T>::LinkedList(){}

	template<typename T>
	_ll<T>::LinkedList(const LinkedList<T>& other)
		:_size(other._size)
	{
		//TODO
	}

	template<typename T>
	_ll<T>::LinkedList<T>(LinkedList&& other)
		:_head(std::move(other._head)),
		_tail(std::move(other._tail)),
		_size(other._size){}


	template<typename T>
	size_t _ll<T>::Size() const { return _size; }

	template<typename T>
	bool _ll<T>::Empty() const { return _size == 0; }
	
	template<typename T>
	auto _ll<T>::PushBack(DataType value)->Iterator
	{
		_AddNode();
		_tail->data = std::make_shared<T>(std::move(value));
		return Iterator{_tail};
	}

	template<typename T>
	auto _ll<T>::PushFront(DataType value)->Iterator
	{
		_AddNode(false);
		_head->data = std::make_shared<T>(std::move(value));
		return Iterator{_head.get()};
	}

	template<typename T>
	auto _ll<T>::_AddNode(bool back)->void
	{
		if (_head == nullptr && _tail == nullptr) {
			_head = std::make_unique<Node>();
			_tail = _head.get();
		}
		else {
			if (back) {
				_tail->next = std::make_unique<Node>();
				_tail->next->prev = _tail;
				_tail = _tail->next.get();
			}
			else {
				auto new_node = std::make_unique<Node>();
				std::unique_ptr<Node> tmp = std::move(_head);
				tmp->prev = new_node.get();
				new_node->next = std::move(tmp);
				_head = std::move(new_node);
			}
		}
		++_size;
	}

	template<typename T>
	auto _ll<T>::PopBack()->Data
	{
		if (_tail != nullptr) {
			NodeRef prev = _tail->prev;
			_tail = prev;
			std::unique_ptr<Node> last = std::move(prev->next);
			--_size;
			return last->data;
		}
		return nullptr;
	}

	template<typename T>
	auto _ll<T>::PopFront()->Data
	{
		if (_head != nullptr) {
			std::unique_ptr<Node> new_head = std::move(_head->next);
			std::unique_ptr<Node> old_head = std::move(_head);
			_head = std::move(new_head);
			--_size;
			return old_head->data;
		}
		return nullptr;
	}

	template<typename T>
	auto _ll<T>::InsertBefore(ConstIter iter, DataType value)->std::pair<bool, Iterator>
	{
		if (!iter) return { false, Iterator{nullptr} };
		NodeRef ref = iter._node;

		if (ref == _head.get()) {
			PushFront(value);
			++_size;
			return { true, Iterator{_head.get()} };
		}
		else {
			ConstIter prev{ref->prev};
			return _InsertAfter(prev, value);
		}
	}

	template<typename T>
	auto _ll<T>::InsertAfter(ConstIter iter, DataType value)->std::pair<bool, Iterator>
	{
		return _InsertAfter(iter, value);
	}

	template<typename T>
	auto _ll<T>::_InsertAfter(ConstIter iter, DataType value)->std::pair<bool, Iterator>
	{
		if (!iter) return { false, Iterator{nullptr} };
		NodeRef ref = iter._node;

		if (ref == _tail)
		{
			PushBack(value);
			++_size;
			return { true, Iterator{_tail} };
		}
		else {
			std::unique_ptr<Node> new_node = std::make_unique<Node>();
			new_node->data = std::make_shared<DataType>(std::move(value));

			new_node->next = std::move(ref->next);
			new_node->next->prev = new_node.get();
			new_node->prev = ref;
			ref->next = std::move(new_node);
			++_size;
			return { true, Iterator{ref->next.get()} };
		}
	}

	template<typename T>
	auto _ll<T>::Delete(ConstIter iter)-> bool
	{
		if (!iter) return false;
		NodeRef ref = iter._node;

		NodeRef prev = ref->prev;
		std::unique_ptr<Node> next = std::move(ref->next);

		if (prev == nullptr) {
			_head = std::move(next);
		}
		else {
			prev->next = std::move(next);
			prev->next->prev = prev;
		}

		--_size;
		return true;
	}

	template<typename T>
	auto _ll<T>::Begin()->Iterator { return Iterator{_head.get()}; }

	template<typename T>
	auto _ll<T>::End()->Iterator { return Iterator{ nullptr }; }

	template<typename T>
	auto _ll<T>::Begin() const ->ConstIter { return ConstIter{ _head.get() }; }

	template<typename T>
	auto _ll<T>::End() const ->ConstIter { return ConstIter{ nullptr }; }

};



#endif // !_LINKED_LIST_H_

