#ifndef __LIST__H__
#define __LIST__H__

#include <mutex>
#include <memory>

namespace parallel 
{
	template<typename T>
	class list
	{

		struct node
		{
			std::mutex				_mutex;
			std::shared_ptr<T>		_data{nullptr};
			std::unique_ptr<node>	_next{nullptr};

			node() = default;
			node(const T const& value)
				:_data(std::make_shared<T>(value))
			{}

		};

	public:
		list() = default;
		list(const list&) = delete;
		list(list&&) = delete;
		list& operator=(const list&) = delete;
		list& operator=(list&&) = delete;
		~list() = default;

		void PushFront(const T& value)
		{
			std::unique_ptr<node> new_node{ new node{value} };
			std::lock_guard<std::mutex> lg{_head._mutex};
			new_node->_next = std::move(_head._next);
			_head._next = std::move(new_node);
		}

		template<typename Function>
		void ForEach(Function func)
		{
			node* current = &_head;
			std::unique_lock<std::mutex> ul{_head._mutex};
			while (node* next = current->_next.get())
			{
				std::unique_lock<std::mutex> next_lk(next->_mutex);
				ul.unlock();
				func(*next->_data);
				current = next;
				ul = std::move(next_lk);
			}
		}

		template<typename Predicate>
		void RemoveIf(Predicate pred)
		{
			node* current = &_head;
			using namespace std;
			unique_lock<mutex> lk{_head._mutex};
			while (node* next = current->_next.get())
			{
				unique_lock<mutex> next_lk{next->_mutex};
				if (pred(*next->_data)) {
					unique_ptr<node> old_next = move(current->_next);
					current->_next = move(next->_next);
					next_lk.unlock();
				}
				else {
					lk.unlock();
					current = next;
					lk = std::move(next_lk);
				}
			}
		}

	private:
		node _head{};
	};
};

#endif // !__LIST__H__
