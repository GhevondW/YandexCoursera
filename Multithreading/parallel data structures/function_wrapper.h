#ifndef _FUNCTION_WRAPPER_H_
#define _FUNCTION_WRAPPER_H_

#include <memory>

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
		struct impl_type : public impl_base
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
		std::unique_ptr<impl_base> _impl{ nullptr };
	};
}

#endif // !_FUNCTION_WRAPPER_H_

