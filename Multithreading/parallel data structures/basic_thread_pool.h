#ifndef _BASIC_THREAD_POOL_H_
#define _BASIC_THREAD_POOL_H_

#include "join_threads.h"
#include <atomic>
#include "queue.h"
#include <functional>

namespace parallel
{
	class basic_thread_pool
	{
		using Task = std::function<void()>;
		using TasksQueue = parallel::queue<Task>;
	public:
		basic_thread_pool()
			:_done(false),
			_threads(),
			_tasks(),
			_joiner(_threads)
		{
			auto thread_count = std::thread::hardware_concurrency();
			try
			{
				for (size_t i = 0; i < (thread_count - 1); ++i)
				{
					_threads.push_back(std::thread(&basic_thread_pool::_WorkerThread, this));
				}
			}
			catch (...)
			{
				_done = true;
				throw;
			}
		}
		~basic_thread_pool()
		{
			_done = true;
		}

		void SubmitTask(Task task)
		{
			_tasks.Push(std::move(task));
		}

	private:

		void _WorkerThread()
		{
			while (!_done)
			{
				Task task;
				if (_tasks.TryPop(task)) {
					task();
				}
				else {
					std::this_thread::yield();
				}
			}
		}

	private:
		std::atomic_bool			_done;
		std::vector<std::thread>	_threads;
		TasksQueue					_tasks;
		join_threads				_joiner;
	};
}

#endif // !_BASIC_THREAD_POOL_H_
