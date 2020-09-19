#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <memory>
#include <mutex>
#include <condition_variable>

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
		std::mutex				_mtx_head{};
		std::mutex				_mtx_tail{};
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

		std::lock_guard<std::mutex> lg_tail{_mtx_tail};

		_tail->_item = new_item;
		_tail->_next = std::move(p);
		_tail = new_tail;
	}

	template<typename T>
	auto queue<T>::TryPop() -> std::shared_ptr<T>
	{
		using namespace std;
		unique_lock<mutex> head_lock{ _mtx_head};
		{
			lock_guard<mutex> tail_lock{_mtx_tail};
			if (_head.get() == _tail) return std::shared_ptr<T>{nullptr};
		}

		std::unique_ptr<node> old_head = std::move(_head);
		_head = std::move(old_head->_next);

		head_lock.unlock();
		return old_head->_item;
	}

	template<typename T>
	auto queue<T>::Empty() const -> bool
	{
		return _head == nullptr && _tail == nullptr;
	}
};

#endif // !_QUEUE_H_

