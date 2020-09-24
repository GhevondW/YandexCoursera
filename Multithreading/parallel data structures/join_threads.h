#ifndef _JOIN_THREADS_H_
#define _JOIN_THREADS_H_

#include <vector>
#include <thread>

namespace parallel
{
	class join_threads
	{
	public:
		join_threads(std::vector<std::thread>& ref)
			:_ref(ref) {}
		~join_threads()
		{
			for (size_t i = 0; i < _ref.size(); i++)
			{
				if (_ref[i].joinable()) {
					_ref[i].join();
				}
			}
		}

	private:
		std::vector<std::thread>& _ref;
	};
}

#endif // !_JOIN_THREADS_H_

