#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <memory>
#include <mutex>
#include <condition_variable>
#include <functional>

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

		auto Push(T value)						-> void;
		auto TryPop()							-> std::shared_ptr<T>;
		auto TryPop(T& value)					-> bool;
		auto WaitPop()							-> std::shared_ptr<T>;
		auto WaitPop(T& value)					-> void;
		auto Empty() const						-> bool;
		auto Iterate(std::function<void(T&)>)	-> void;

	private:

		std::unique_ptr<node> _WaitPopHead()
		{
			using namespace std;
			unique_lock<mutex> ul{ _mtx_head };
			_pop_cond.wait(ul, [this]()
				{
					lock_guard<mutex> lg{ _mtx_tail };
					return _head.get() != _tail;
				});

			std::unique_ptr<node> old_head = std::move(_head);
			_head = std::move(old_head->_next);
			return std::move(old_head);
		}

		std::unique_ptr<node> _PopHead()
		{
			using namespace std;
			unique_lock<mutex> head_lock{ _mtx_head };
			{
				lock_guard<mutex> tail_lock{ _mtx_tail };
				if (_head.get() == _tail) return std::unique_ptr<node>{nullptr};
			}

			std::unique_ptr<node> old_head = std::move(_head);
			_head = std::move(old_head->_next);

			return std::move(old_head);
		}

	private:
		std::unique_ptr<node>	_head{nullptr};
		node*					_tail{nullptr};
		std::mutex				_mtx_head{};
		std::mutex				_mtx_tail{};
		std::condition_variable	_pop_cond{};
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
		node* new_tail = p.get();

		{
			std::lock_guard<std::mutex> lg_tail{ _mtx_tail };

			_tail->_item = new_item;
			_tail->_next = std::move(p);
			_tail = new_tail;
		}
		_pop_cond.notify_one();
	}

	template<typename T>
	auto queue<T>::TryPop() -> std::shared_ptr<T>
	{
		auto old_head = _PopHead();
		return old_head ? old_head->_item : nullptr;
	}

	template<typename T>
	auto queue<T>::TryPop(T& value) -> bool
	{
		auto old_head = _PopHead();
		if (old_head) {
			value = std::move(*old_head->_item);
		}
		return old_head != nullptr;
	}

	template<typename T>
	auto queue<T>::WaitPop() -> std::shared_ptr<T>
	{
		auto old_head = _WaitPopHead();
		return std::move(old_head->_item);
	}

	template<typename T>
	auto queue<T>::WaitPop(T& value) -> void
	{
		auto old_head = _WaitPopHead();
		value = std::move(*old_head->_item);
	}

	template<typename T>
	auto queue<T>::Empty() const -> bool
	{
		return _head == nullptr && _tail == nullptr;
	}

	template<typename T>
	auto queue<T>::Iterate(std::function<void(T&)> func) -> void
	{
		std::lock(_mtx_head, _mtx_tail);
		std::lock_guard<std::mutex> lg_head{_mtx_head, std::adopt_lock};
		std::lock_guard<std::mutex> lg_tail{_mtx_tail, std::adopt_lock};

		node* head = _head.get();
		while (head != _tail)
		{
			func(*head->_item);
			head = head->_next.get();
		}
		//TODO all queue iterator
	}

};

#endif // !_QUEUE_H_

