#ifndef _THREAD_POOL_FW_H_
#define _THREAD_POOL_FW_H_

//FW aka function wrapper

#define _ne noexcept

#include "join_threads.h"
#include <atomic>
#include "queue.h"
#include <functional>
#include <future>

namespace parallel
{

	class function_wrapper
	{

		struct impl_base
		{
			virtual void call() = 0;
			virtual ~impl_base() {}
		};

		template<typename Function>
		struct impl_type: public impl_base
		{
			Function f;
			impl_type(Function&& f_) :f(std::move(f_)) {}
			void call() override 
			{
				f();
			}
		};

	public:

		template<typename Function>
		function_wrapper(Function func)
			:_impl(new impl_type<Function>(std::move(func)))
		{}
		function_wrapper() = default;

		function_wrapper(function_wrapper&& other) _ne
			:_impl(std::move(other._impl))
		{}

		function_wrapper& operator=(function_wrapper&& other) _ne
		{
			_impl = std::move(other._impl);
			return *this;
		}

		void operator()() 
		{
			if (_impl) {
				_impl->call();
			}
		}

		function_wrapper(const function_wrapper& other) = delete;
		function_wrapper(function_wrapper& other) = delete;
		function_wrapper& operator=(const function_wrapper& other) = delete;

	private:
		std::unique_ptr<impl_base> _impl{nullptr};
	};


	class thread_pool_fw
	{
		using Task = function_wrapper;
		using TasksQueue = parallel::queue<function_wrapper>;
	public:
		thread_pool_fw()
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
					_threads.push_back(std::thread(&thread_pool_fw::_WorkerThread, this));
				}
			}
			catch (...)
			{
				_done = true;
				throw;
			}
		}
		~thread_pool_fw()
		{
			_done = true;
		}

		template<typename Function>
		std::future<typename std::result_of<Function()>::type> Submit(Function func)
		{
			using result_type = typename std::result_of<Function()>::type;
			std::packaged_task<result_type()> task(std::move(func));
			auto res = task.get_future();
			_tasks.Push(std::move(task));
			return res;
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
		TasksQueue					_tasks;
		std::vector<std::thread>	_threads;
		join_threads				_joiner;
	};

}

#endif // !_THREAD_POOL_FW_H_

