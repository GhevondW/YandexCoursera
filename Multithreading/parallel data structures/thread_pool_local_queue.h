#ifndef _THREAD_POOL_LOCAL_QUEUE_H_
#define _THREAD_POOL_LOCAL_QUEUE_H_

#include "function_wrapper.h""
#include <future>
#include <vector>
#include <queue>
#include "queue.h"
#include "join_threads.h"

#define S_TL	static thread_local //each thread will have its own copy of this kinde of variable
#define STAT	static
#define TL		thread_local
#define uptr	std::unique_ptr

namespace parallel
{

	class thread_pool_local_queue
	{
		using Task = function_wrapper;
		using TasksQueue = parallel::queue<Task>;
		using LocalQueue = std::queue<Task>;
		using LocalTasks = std::unique_ptr<LocalQueue>;

	public:

		using LocalQueueType = std::queue<function_wrapper>;

	public:
		thread_pool_local_queue()
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
					_threads.push_back(std::thread(&thread_pool_local_queue::_WorkerThread, this));
				}
			}
			catch (...)
			{
				_done = true;
				throw;
			}
		}
		~thread_pool_local_queue()
		{
			_done = true;
		}

		template<typename Function>
		std::future<typename std::result_of<Function()>::type> Submit(Function func)
		{
			using result_type = typename std::result_of<Function()>::type;
			std::packaged_task<result_type()> task(std::move(func));
			auto res = task.get_future();
			if (_local_tasks) {
				_local_tasks->push(std::move(task));
			}
			else {
				_tasks.Push(std::move(task));
			}
			return res;
		}

	private:

		void _WorkerThread()
		{
			_local_tasks.reset(new LocalQueue());
			while (!_done)
			{
				Task task;
				if (_local_tasks && !_local_tasks->empty())
				{
					task = std::move(_local_tasks->front());
					_local_tasks->pop();
					task();
				}
				else {
					if (_tasks.TryPop(task))
					{
						task();
					}
					else {
						std::this_thread::yield();
					}
				}
			}
		}

	private:

		 
		

		std::atomic_bool				_done;
		S_TL uptr<LocalQueueType>		_local_tasks;
		TasksQueue						_tasks;
		std::vector<std::thread>		_threads;
		join_threads					_joiner;
	};

	TL uptr<thread_pool_local_queue::LocalQueueType> thread_pool_local_queue::_local_tasks = nullptr;

}

#endif // !_THREAD_POOL_LOCKAL_QUEUE_H_

